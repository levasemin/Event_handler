#include "GraphicLib.h"

#include <iostream>
#include <vector>

void left_click(Button *self, Vector2d point)
{
    std::cout << " !!! " << point.x_ << " " << point.y_ << std::endl;
}

void right_click(Button *self, Vector2d point)
{
    std::cout << point.x_ << " !!!! " << point.y_ << " " << std::endl;
}

void left_click(Widget *self, Vector2d point)
{
    std::cout << "Window" << " " << point.x_ << " " << point.y_ << std::endl;
}

void right_click(Widget *self, Vector2d point)
{
    std::cout << point.x_ << " " << point.y_ << "Window" << std::endl; 
}

void press_key(Widget *self, int key)
{
    std::cout << "Window key " << key << std::endl;
}


const char *path_british = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

int main()
{          
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Color::Yellow));

    Container main_container(Vector2d(500, 500), Vector2d(500, 400));
    main_container.set_texture(Texture(Color::Green));

    Container container(Vector2d(100, 400), Vector2d(50, 200));
    
    DecoratorScroll scroll_container = DecoratorScroll(&container);

    Button first_button (Vector2d(100, 300), Vector2d(50, 160), Texture(Color::Blue));

    Command<const Event&> *command = (Command<const Event &> *)new SimpleCommand<Button, const Event&>(&first_button, &Button::print);

    first_button.set_left_click(command);
    first_button.set_right_click(command);

    Button second_button(Vector2d(100, 400),  Vector2d(50, 520), Texture(path_british));
    second_button.set_left_click (command);
    second_button.set_right_click(command);

    Button third_button (Vector2d(100, 200), Vector2d(50, 830), Texture(path_british));
    third_button.set_left_click (command);
    third_button.set_right_click(command);

    Image image(path_british);

    scroll_container.add(&first_button);

    scroll_container.add(&second_button);
    scroll_container.add(&third_button);
    DecoratorScrollBar decorator(&scroll_container);

    Font font("/home/levce/projectsDED/event_handler2/Event_handler/fonts/ofont.ru_Times New Roman.ttf");
    Text text(font);
    text.setString("YAYAYA\n");
    
    first_button.set_text(text);

    main_container.add(&decorator);
    
    main_window.add(&main_container);

    std::vector<Widget *> main_container_widget_ = main_container.get_children();
    
    for (int i = 0; i < main_container_widget_.size(); i++)
    {
        main_container.remove(main_container_widget_[i]);
    }

    main_container.add(&decorator);

    Application app(&main_window);

    app.exec();
}