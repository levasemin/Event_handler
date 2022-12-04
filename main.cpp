#include "GraphicLib.h"

#include <iostream>
#include <vector>


const char *path_british = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";
const char *path_mountain = "/home/levce/projectsDED/event_handler2/Event_handler/source/mountain.jpg";

int main()
{          
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Color::Grey));

    TextureManager &texture_manager = TextureManager::getInstance();
    texture_manager.load_textures("Textures");

    Image image(path_mountain);
    ToolPalette tool_palette(Vector2d(300, 300), Vector2d(160, 173), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    Container setting_container(Vector2d(300, 588), Vector2d(160, 700));
    setting_container.set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));

    Canvas canvas(Vector2d(1400, 970), Vector2d(1020, 508), image, &tool_palette, &setting_container);

    SuperToolPaint super_tool_paint;

        
    DecoratorScroll scroll_canvas(&canvas);
    DecoratorScrollBar scroll_bar_canvas(&scroll_canvas);

    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
        
    Editor edit(Vector2d(100, 20), Vector2d(300, 300));
    
    Application app(&main_window);
    
    app.exec();
}