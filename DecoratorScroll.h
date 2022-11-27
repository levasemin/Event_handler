#include "Decorator.h"

class DecoratorScroll : public Decorator
{
    Vector2d global_offset0_ = (0, 0);

public :
    DecoratorScroll(Widget *widget) : Decorator(widget)
    {
    }

    void ScrollEvent (const Event &event) override
    {
        if (point_belonging(Vector2d(event.Oleg_.sedata.x, event.Oleg_.sedata.y)))
        {
            set_local_offset(Vector2d(0, get_local_offset().y_ + event.Oleg_.sedata.value * 10.0));   
        }
    }

    void set_local_offset(Vector2d offset) override
    {       
        offset.x_ = offset.x_ <= 0 ? offset.x_ : 0;
        offset.y_ = offset.y_ <= 0 ? offset.y_ : 0;
        
        Vector2d max_offset = get_shape() - get_global_shape();
        
        if (max_offset.x_ < 0)
        {
            offset.x_ = offset.x_ >= max_offset.x_ ? offset.x_ : max_offset.x_;
        }

        if (max_offset.y_ < 0)
        {
            offset.y_ = offset.y_ >= max_offset.y_ ? offset.y_ : max_offset.y_;
        }
        
        Decorator::set_local_offset(offset);
    }

    void add(Widget *widget) override
    {
        widget_->add(widget);
    }
};