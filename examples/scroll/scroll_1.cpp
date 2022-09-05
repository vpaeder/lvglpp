#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void scroll_1() {
        /*Create an object with the new style*/
        static auto panel = Container(scr_act());
        panel.set_size(200, 200);
        panel.center();
        static auto child1 = Container(panel);
        child1.set_pos(0, 0);
        child1.set_size(70, 70);
        static auto label1 = Label(child1);
        label1.set_text("Zero");
        label1.center();

        static auto child2 = Container(panel);
        child2.set_pos(160, 80);
        child2.set_size(80, 80);
        static auto btn = Button(child);
        static auto label2 = Label(btn);
        label2.set_text("Right");
        label2.center();

        static auto child3 = Container(panel);
        child3.set_pos(40, 160);
        child3.set_size(100, 70);
        static auto label3 = Label(child3);
        label3.set_text("Bottom");
        label3.center();        
    }
}