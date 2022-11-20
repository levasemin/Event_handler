#include "Image.h"
#include "Widget.h"
#include "Object.h"

class Surface : public Image, public Object 
{
public:

    Surface(Vector2d shape, Vector2d center, const Image &image, Widget *parent = nullptr) : Image(image), Object(shape, center, image.getTexture(), parent)
    {}

    void set_image(const Image &new_image)
    {
        
    }
};