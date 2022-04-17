#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/button.h" // for Button
#include "lvglpp/widgets/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void scroll_1() {
        /*Create an object with the new style*/
        auto panel = Container(scr_act());
        panel.set_size(200, 200);
        panel.center();
        auto child1 = Container(panel);
        child1.set_pos(0, 0);
        child1.set_size(70, 70);
        auto label1 = Label(child1);
        label1.set_text("Zero");
        label1.center();

        auto child2 = Container(panel);
        child2.set_pos(160, 80);
        child2.set_size(80, 80);
        auto btn = Button(child);
        auto label2 = Label(btn);
        label2.set_text("Right");
        label2.center();

        auto child3 = Container(panel);
        child3.set_pos(40, 160);
        child3.set_size(100, 70);
        auto label3 = Label(child3);
        label3.set_text("Bottom");
        label3.center();        
    }
}