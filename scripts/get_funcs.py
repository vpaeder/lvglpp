import re
import json
import os


self_arg = "this->raw_ptr()"

base_path = "components/lvgl/src"
gen_path = "autogen/build"
tmpl_path = "autogen/template"

templates = []
classes = {}

mods = ["", "*", "&"]
class TypeCast(object):
    def __init__(self, cpp_type:str, var_cast:str="{}"):
        self.cpp_type = cpp_type
        self.conv_types = dict()
        self.conv_ret_types = dict()
        [self.set_mod(mod, mod) for mod in mods]
        [self.set_ret_mod(mod, mod) for mod in mods]
        self.var_cast = var_cast

    def set_mod(self, c_mod:str, cpp_mod:str) -> None:
        self.conv_types[c_mod] = "{name}{mod}".format(name=self.cpp_type, mod=cpp_mod if cpp_mod=="" else " {}".format(cpp_mod))

    def set_ret_mod(self, c_mod:str, cpp_mod:str) -> None:
        self.conv_ret_types[c_mod] = "{name}{mod}".format(name=self.cpp_type, mod=cpp_mod if cpp_mod=="" else " {}".format(cpp_mod))

    def __getitem__(self, __name: str):
        if __name in self.conv_types:
            return self.conv_types[__name]
        else:
            return ""
    
    def get_ret_type(self, mod:str):
        return self.conv_ret_types[mod]

    def cast_var(self, name:str) -> str:
        return self.var_cast.format(name)
    

conv_args = {
    "lv_obj_t":TypeCast("Object"),
    "lv_disp_t":TypeCast("Display"),
    "lv_indev_t":TypeCast("InputDevice"),
    "lv_timer_t":TypeCast("Timer"),
    "lv_anim_t":TypeCast("Animation"),
    "lv_event_t":TypeCast("Event"),
    "lv_group_t":TypeCast("Group"),
    "lv_style_t":TypeCast("Style"),
    "lv_style_transition_dsc_t":TypeCast("StyleTransition"),
    "lv_color_filter_dsc_t":TypeCast("ColorFilter"),
    "lv_theme_t":TypeCast("Theme"),
    "lv_draw_rect_dsc_t":TypeCast("RectangleDrawDescriptor"),
    "lv_draw_label_dsc_t":TypeCast("LabelDrawDescriptor"),
    "lv_draw_img_dsc_t":TypeCast("ImageDrawDescriptor"),
    "lv_draw_line_dsc_t":TypeCast("LineDrawDescriptor"),
    "lv_draw_arc_dsc_t":TypeCast("ArcDrawDescriptor"),
    "lv_img_decoder_dsc_t":TypeCast("ImageDecoder"),
    "lv_img_header_t":TypeCast("ImageHeader"),
    "lv_img_dsc_t":TypeCast("ImageDescriptor"),
    "lv_draw_mask_line_param_t":TypeCast("LineMask"),
    "lv_draw_mask_angle_param_t":TypeCast("AngleMask"),
    "lv_draw_mask_radius_param_t":TypeCast("RadiusMask"),
    "lv_draw_mask_fade_param_t":TypeCast("FadeMask"),
    "lv_draw_mask_map_param_t":TypeCast("MapMask"),
    "lv_draw_mask_polygon_param_t":TypeCast("PolygonMask"),
    "lv_font_t":TypeCast("Font"),
    "lv_area_t":TypeCast("Area"),
    "lv_fs_drv_t":TypeCast("FileSystem"),
    "lv_fs_file_t":TypeCast("File"),
    "lv_fs_dir_t":TypeCast("Directory"),
    "char":TypeCast("std::string"),
    "lv_obj_class_t":TypeCast("lv_obj_class_t"),
    }
for arg in conv_args:
    conv_args[arg].set_mod("*", "&")
    for mod in mods:
        conv_args[arg].set_ret_mod(mod, "")
    conv_args[arg].var_cast = "{}.raw_ptr()"

conv_args["char"].var_cast = "{}.c_str()"

conv_args["lv_obj_class_t"].set_mod("*", "&")
conv_args["lv_obj_class_t"].var_cast = "&{}"
conv_args["lv_obj_class_t"].set_ret_mod("*", "*")

def check_path_exists(file_path):
    path,fname = os.path.split(file_path)
    if not os.path.exists(path):
        os.makedirs(path)

class Argument():
    def __init__(self, arg:str, is_return:bool=False):
        self.is_const = False
        self.is_cpp = False
        # extracts info from a string such as: const struct _type_t * name
        argtype = re.search(r'(?:(?:(?P<const>const)|(?P<struct>struct)|)\s*)+\s*(?P<type>(?:\w+)+\s*)(?P<mod>\**|&*)\s*(?P<name>\w*)', arg)
        self.raw_type = arg # store raw type in case nothing could be extracted
        if argtype is not None:
            self.obj_type = argtype.groupdict()["type"].strip()
            self.is_const = argtype.groupdict()["const"] is not None
            self.mod = argtype.groupdict()["mod"] if argtype.groupdict()["mod"] is not None else ""
            self.name = argtype.groupdict()["name"].strip()
            if argtype.groupdict()["struct"] is not None: self.obj_type = self.obj_type[1:]
            self.raw_type = "{const}{type}{sp}{mod} {name}".format(
                const="const " if self.is_const else "",
                type=self.obj_type,
                sp="" if self.mod=="" else " ",
                mod=self.mod,
                name=self.name)
            if self.obj_type in conv_args:
                self.cpp_type = "{const}{type} {name}".format(
                    const="const " if self.is_const else "",
                    type=conv_args[self.obj_type].get_ret_type(self.mod) if is_return else conv_args[self.obj_type][self.mod],
                    name=self.name)
                self.is_cpp = True
    
    def __str__(self) -> str:
        return self.cpp_type if self.is_cpp else self.raw_type
    
    def as_l_value(self) -> str:
        if self.is_cpp and self.obj_type in conv_args:
            return conv_args[self.obj_type].cast_var(self.name)
        else:
            return self.name
    

class Function():
    def __init__(self, name:str, rettype:str, args:'list[str]'):
        self.name = name
        self.rettype = Argument(rettype.strip(), is_return=True)
        self.args = [Argument(a.strip()) for a in args]
    
    def __repr__(self) -> str:
        return "{rettype}{name}({args})".format(
            rettype=self.rettype,
            name=self.name,
            args=", ".join([str(a) for a in self.args])
        )
    
    def _get_cls(self) -> str:
        cls = re.search(r'((?:[a-zA-Z0-9]+_)+)', str(self.args[0].raw_type))
        if cls is None: return None
        return cls.groups()[0]

    def is_of_class(self, obj_type=None) -> bool:
        if len(self.args)==0 and obj_type is not None: return False
        cls = self._get_cls()
        if cls is None and obj_type is None: return True
        if cls is None: return False
        return cls == obj_type
    
    def is_member_function(self) -> bool:
        if len(self.args)==0: return False
        cls = self._get_cls()
        if cls is None: return False
        return self.name.startswith(cls)
    
    def get_cpp_impl(self, obj_type=None, cpp_cls=None) -> str:
        return self.__to_cpp(obj_type, "{}::".format(cpp_cls) if cpp_cls is not None and cpp_cls != "" else "")

    def get_cpp_def(self, obj_type=None) -> str:
        return self.__to_cpp(obj_type)

    def __to_cpp(self, obj_type=None, cpp_cls=None) -> str:
        if not self.is_of_class(obj_type):
            return ""
        is_impl = cpp_cls is not None
        prefix = cpp_cls if is_impl else ""
        # suffix for 1st line: in header, ;, in impl, {
        suffix = " {" if is_impl else ";"
        # different treatment if 1st arg is const;
        # this is normal for a getter and not for a setter;
        # for a getter, if it is not const, we const_cast
        is_const = self.args[0].is_const
        # definition string
        cpp_def = ""
        # gets cpp class
        cls = self._get_cls() if self._get_cls() is not None else ""
        start_idx = 1 if self.is_member_function() else 0
        if self.rettype.obj_type == "void":
            # if setter, rettype is void
            cpp_def = "{rettype}{cpp_cls}{name}({args}){suffix}".format(
                rettype=self.rettype,
                cpp_cls=prefix,
                name=self.name.replace(cls, ""),
                args=", ".join([str(a).strip() for a in self.args[start_idx:] if not (a.obj_type=="void" and a.mod=="")]),
                suffix=suffix)
        else:
            # if getter, we declare it const
            cpp_def = "{rettype}{cpp_cls}{name}({args}){const}{suffix}".format(
                rettype=self.rettype,
                cpp_cls=prefix,
                name=self.name.replace(cls, ""),
                args=", ".join([str(a).strip() for a in self.args[start_idx:] if not (a.obj_type=="void" and a.mod=="")]),
                const=" const" if is_const else "",
                suffix=suffix)
        
        # this is when we generate an implementation file;
        # we need to add a call to the underlying function;
        # for a setter, we don't need to return anything;
        # for a getter, we do, and we also have to take care
        # of non-const 1st argument;
        # moreover, if return type is a C++ class, we need to convert
        if is_impl:
            if self.is_member_function():
                # format first argument for member function
                const_cls_arg = "const_cast<{cls}t>({selfarg})".format(cls=cls, selfarg=self_arg)
                args = [const_cls_arg if is_const and not self.args[0].is_const else self_arg] + [a.as_l_value() for a in self.args[1:]]
            else:
                # not a member function => all args treated the same
                args = [a.as_l_value() for a in self.args]
            # C function call
            c_func = "{name}({args})".format(
                name=self.name,
                args=", ".join(args)
            )
            # if C++ class, need conversion
            if self.rettype.is_cpp:
                c_func = "{cpp_cls}({func}, false)".format(cpp_cls=conv_args[self.rettype.obj_type][""], func=c_func)
            # format function call
            cpp_def += "\n\t{retinst}{func};\n}}".format(
                retinst="return " if self.rettype!="void" else "",
                func=c_func
            )
        return cpp_def


class HeaderFile(object):
    '''Class used to parse a header file to extract function definitions.
    '''
    def __init__(self, path:str, exclude:'list[str]'=[]):
        '''Constructor.

        Parameters:
            path(str): file path
            exclude(list[str]): list of functions to exclude
        '''
        self.funcs = []
        self.exclude = exclude
        # this is a regex that matches function definitions and captures a number of things in named groups:
        #   - rettype: return type including modifiers (const/*/&)
        #   - name: function name
        #   - args: arguments, as written
        # remove up to 3 macros, inline and static keywords
        regex = re.compile(r'\n\s*(?:(?:inline|static|[A-Z_]+)\s+){0,3}(?!else|typedef|return)(?P<rettype>(?:\w+(?:\*|)*\s+(?:\*|)*)+)\s*?_*(?P<name>\w+)\s*\((?P<args>[\w\d\s\*\&,]*)\)\s*(?:;|)\n')
        # open file
        with open(path, "r") as f:
            data = f.read()
        # search for 1st definition
        res = regex.search(data)
        while res is not None:
            # add definitions to list until none can be found anymore
            self.funcs.append(Function(res.groupdict()["name"].strip(),
                              res.groupdict()["rettype"].strip(),
                              res.groupdict()["args"].split(",")))
            res = regex.search(data, res.end())

    def get_functions(self, obj_class=None) -> 'list[Function]':
        '''Get functions matching a given class.

        Parameters:
            obj_class(str or None): C object class prefix (e.g. lv_obj_); if None, get free functions.
        
        Returns:
            list[Function]: a list of functions matching request.
        '''
        return [fct for fct in self.funcs if fct.is_of_class(obj_class) and not fct.name in self.exclude]
        

class Class(object):
    '''Class representing a C++ class.
    '''
    def __init__(self, name:str, obj_type:str):
        '''Constructor.

        Parameters:
            name(str): C++ class name
            obj_type(str): C object type (e.g. lv_obj_t)
        '''
        self.name = name
        self.obj_type = obj_type
        self.functions = dict()
    
    def add_function(self, fct:Function, obj_type:str) -> None:
        '''Add function associated with given C object type.

        Parameters:
            fct(Function): function to add
            obj_type(str): C object type (e.g. lv_obj_t)
        '''
        if obj_type not in self.functions:
            self.functions[obj_type] = []
        self.functions[obj_type].append(fct)
    
    def get_obj_class(self) -> str:
        '''Get C object class prefix (e.g. if self.obj_type = lv_obj_t, returns lv_obj_)

        Returns:
            str: C object class prefix
        '''
        match = re.match("^(?P<ocls>(?:[A-Za-z0-9]+_)+)", self.obj_type)
        if match is None: return self.obj_type
        return match.groupdict()["ocls"]

    def render_impl(self):
        '''Render implementation.

        Returns:
            str: function implementations as a text string.
        '''
        res = ""
        for obj_type in self.functions:
            res += "\n".join([fct.get_cpp_impl(obj_type, self.name) for fct in self.functions[obj_type]])
        return res

    def render_hdr(self):
        '''Render header.

        Returns:
            str: function definitions as a text string.
        '''
        res = ""
        for obj_type in self.functions:
            res += "\n".join([fct.get_cpp_def(obj_type) for fct in self.functions[obj_type]])
        return res


class Template(object):
    '''Class describing a h/cpp file template.
    '''
    def __init__(self, name:str, classes:'list[str]', file_h:str, file_cpp:str, base_path:str = "autogen/template"):
        '''Constructor.

        Parameters:
            name(str): template name (this is used to assign free functions)
            classes(list[str]): list of C++ classes that should be included
            file_h(str): relative path to header file (template and generated)
            file_cpp(str): relative path to implementation file (template and generated)
            base_path(str): base path for templates
        '''
        self.name = name
        self.classes = classes
        self.file_h = file_h
        self.file_cpp = file_cpp
        if len(file_h)>0:
            full_path = os.path.join(base_path, file_h)
            check_path_exists(full_path)
            with open(full_path, "r") as f:
                self.data_h = f.read()
        if len(file_cpp)>0:
            full_path = os.path.join(base_path, file_cpp)
            check_path_exists(full_path)
            with open(full_path, "r") as f:
                self.data_cpp = f.read()

    def _get_indent(self, data:str, tk_name:str) -> str:
        '''Get indentation for given token name.

        Parameters:
            data(str): data where to search for token
            tk_name(str): token name
        
        Returns:
            str: string used to indent token, or empty string if token couldn't be found.
        '''
        prefix = ""
        # find where to extract indent
        pos = data.find("%%{}%%".format(tk_name))
        # get pos of beginning of line
        if pos > 0:
            lpos = pos
            while lpos>=0:
                if data[lpos] == '\n': break
                lpos-=1
            if lpos>=0:
                prefix = data[lpos+1:pos]
        return prefix
    
    def _get_token_line(self, data:str, tk_name:str) -> str:
        '''Get indented token.

        Parameters:
            data(str): data where to search for token
            tk_name(str): token name
        
        Returns:
            str: indented token
        '''
        return "{prefix}%%{tk_name}%%".format(prefix=self._get_indent(data, tk_name), tk_name=tk_name)

    def _indent(self, data:str, cls_stub:str, tk_name:str) -> str:
        '''Indent given stub to insert in place of given token.

        Parameters:
            data(str): data where to search for token
            cls_stub(str): data stub to indent
            tk_name(str): token name
        
        Returns:
            str: indented stub
        '''
        prefix = self._get_indent(data, tk_name)
        if len(prefix) > 0:
            stub_lines = cls_stub.split("\n")
            return "\n".join(["{prefix}{line}".format(prefix=prefix,line=line) for line in stub_lines])
        return cls_stub

    def render_hdr(self) -> str:
        '''Render header file.
        
        Returns:
            str: header with rendered function definitions.
        '''
        for cls_id in self.classes + [self.name]:
            # get content
            cls_stub = classes[cls_id].render_hdr()
            # indent lines to match template token indentation
            cls_name = classes[cls_id].name
            cls_stub = self._indent(self.data_h, cls_stub, cls_name)
            token = self._get_token_line(self.data_h, cls_name)
            # insert in template
            self.data_h = self.data_h.replace(token, cls_stub)
        return self.data_h

    def render_impl(self):
        '''Render implementation file.
        
        Returns:
            str: implementation file with rendered function implementations.
        '''
        for cls_id in self.classes + [self.name]:
            # get content
            cls_stub = classes[cls_id].render_impl()
            # indent lines to match template token indentation
            cls_name = classes[cls_id].name
            cls_stub = self._indent(self.data_cpp, cls_stub, cls_name)
            token = self._get_token_line(self.data_cpp, cls_name)
            # insert in template
            self.data_cpp = self.data_cpp.replace(token, cls_stub)
        return self.data_cpp


# open JSON model
with open("scripts/model.json", "r") as f:
    js = json.loads(f.read())

# build list of classes
for cls in js["classes"]:
    classes[cls["cpp"]] = Class(name=cls["cpp"], obj_type=cls["c"])

# build list of templates
for tmpl in js["templates"]:
    templates.append(Template(**tmpl))
    
# read all C header files
for f in js["files"]:
    hdr = HeaderFile(
        path="{base}/{file}".format(base=base_path, file=f["path"]),
        exclude=f["exclude"] if "exclude" in f else []
    )
    # extract class member functions
    for cls_id in classes:
        cls = classes[cls_id]
        obj_class = cls.get_obj_class()
        # only add member functions
        if obj_class is not None:
            [cls.add_function(fct, obj_class) for fct in hdr.get_functions(obj_class)]
    # store free functions in a "class" of its own
    if f["free_func_group"] not in classes:
        classes[f["free_func_group"]] = Class("","")
    [classes[f["free_func_group"]].add_function(fct,None) for fct in hdr.get_functions(None)]

# render files
for tmpl in templates:
    if len(tmpl.file_h)>0:
        full_path = os.path.join(gen_path, tmpl.file_h)
        check_path_exists(full_path)
        with open(full_path, "w") as f:
            f.write(tmpl.render_hdr())
    
    if len(tmpl.file_cpp)>0:
        full_path = os.path.join(gen_path, tmpl.file_cpp)
        check_path_exists(full_path)
        with open(full_path, "w") as f:
            f.write(tmpl.render_impl())
