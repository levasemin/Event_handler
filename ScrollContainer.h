#pragma once

#include "Widget.h"
#include "Texture.h"
#include "Vector2d.h"
#include "Container.h"

class ScrollContainer : public Container
{
protected:
    Vector2d global_offset0_ = (0, 0);

public:

    ScrollContainer(Vector2d shape, Vector2d center, Texture color, Widget *parent = nullptr, std::vector<Widget *> children = {}):
        Container(shape, center, color, parent, children)
        {
        };

//TODO:
//из декоратора поступает сигнал о прокрутке, но scroll container обрубает его, тк он делает проверку на принадлежность точки
    void ScrollEvent (Vector2d point, Vector2d offset) override
    {
        if (offset.y_ > 0)
        {
            offset.x_ = offset.x_ <= -global_offset0_.x_ ? offset.x_ :  -global_offset0_.x_;
            offset.y_ = offset.y_ <= -global_offset0_.y_ ? offset.y_ :  -global_offset0_.y_;
        }
        
        if (offset.y_ < 0)
        {
            Vector2d max_offset =  global_offset0_ + global_shape_ - shape_;
            offset.x_ = -offset.x_ <= max_offset.x_ ? offset.x_ : - max_offset.x_;
            offset.y_ = -offset.y_ <= max_offset.y_ ? offset.y_ : - max_offset.y_;
        }

        global_offset0_ += offset;

        set_local_offset(offset);
    }
};