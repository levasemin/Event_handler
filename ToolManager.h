#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Tool.h"
#include "ToolPalette.h"
#include "Container.h"
#include <vector>
#include "SimpleCommand.h"
#include "Surface.h"
#include <deque>

const int MAX_BACKUP = 32;

class ToolManager
{
private:
    std::vector<booba::Tool *> tools_;

    booba::Tool* active_tool_ = nullptr;
    
    ToolManager(): 
        tools_({}),
        setting_palettes_({})
    {}

    ToolManager( const ToolManager &source):
        tools_(source.tools_),
        active_tool_(source.active_tool_),
        tool_palette_(source.tool_palette_),
        setting_field_(source.setting_field_),
        setting_palettes_(source.setting_palettes_)
    {}

    ToolManager& operator=(const ToolManager& source)
    {
        tools_            = source.tools_;
        active_tool_      = source.active_tool_;
        tool_palette_     = source.tool_palette_;
        setting_field_    = source.setting_field_;
        setting_palettes_ = source.setting_palettes_;

        return *this;
    }
    
public:
    booba::Tool *init_tool_ = nullptr;

    ToolPalette *tool_palette_ = nullptr;
    Container *setting_field_ = nullptr;
    
    std::vector<Container *> setting_palettes_;
    
    Surface *surface_ = nullptr;

    static ToolManager& getInstance()
    {
        static ToolManager instance;
        return instance;
    }    

    void set_tool_palette(ToolPalette *tool_palette)
    {
        tool_palette_ = tool_palette;
    }

    void set_setting_field(Container *setting_palette)
    {
        setting_field_ = setting_palette;
    }

    Container *get_setting_field()
    {
        return setting_field_;
    }

    void add(booba::Tool *new_tool)
    {
        tools_.push_back(new_tool);
        
        Button *tool_button_ = new Button(Vector2d(50, 50), Vector2d(25, 25));
        
        tool_button_->set_texture(tool_palette_->get_texture());
        tool_button_->set_texture(Texture(new_tool->getTexture()));
        tool_button_->set_left_click((Command<const Event &> *) new SimpleCommand<ToolManager, const Event &>(this, &ToolManager::tool_choose));
        tool_button_->set_pressed(true);
        tool_palette_->add(tool_button_);
        
        Container *setting_palette = new Container(Vector2d(setting_field_->get_shape()), Vector2d(setting_field_->get_shape()) / 2);
        setting_palette->set_texture(setting_field_->get_texture());
        setting_palettes_.push_back(setting_palette);
        init_tool_ = new_tool;

        new_tool->buildSetupWidget();
    }
    
    void tool_choose(const Event &event)
    {        
        std::vector<Widget *> tool_palette_children = tool_palette_->get_children();
        
        for (size_t i = 0; i < tool_palette_children.size(); i++)
        {
            if ((uint64_t)tool_palette_children[i] == event.Oleg_.bcedata.id)
            {
                if (active_tool_ != tools_[i])
                {
                    set_active_tool(tools_[i]);
                }
                
                else
                {
                    remove_active_tool(); 
                }
            }

            else
            {
                ((Button *)(tool_palette_children[i]))->is_pressed_ = false;
            }
        }
    }

    void create_memento(Surface *surface)
    {                
        if (numCommands_ == max_backup_ - 1)
        {
            mementoList_.pop_front();
            mementoList_.push_back(nullptr);
            numCommands_--;
        }

        numCommands_++;

        mementoList_[numCommands_] = surface->createMemento();
        max_forward_ = numCommands_;
    }
    
    void apply(Surface *surface, const Event *event)
    {
        if (active_tool_)
        {
            if (event->type_ == EventType::MouseReleased || event->type_ == EventType::CanvasMPressed)
            {
                create_memento(surface);
            }

            booba::Event booba_event   = convert_event(*event);
            active_tool_->apply(&surface->image_, &booba_event);
        }
    }

    static void undo(Surface *surface)
    {
        if (numCommands_ == 0)
        {
            std::cout << "undo fuck up" << std::endl;
            return ;
        }

        surface->reinstateMemento(mementoList_[numCommands_ - 1]);
        numCommands_--;
    }
    
    static void redo(Surface *surface)
    {
        if (numCommands_ >= max_forward_)
        {
            std::cout << "redo fuck up" << std::endl;
            return ;
        }

        surface->reinstateMemento(mementoList_[numCommands_ + 1]);

        numCommands_++;
    }

    void remove_active_tool()
    {
        // setting_field_->remove((Container *) active_tool_->get_setting_widget());
        active_tool_ = nullptr;
    }

    void set_surface(Surface *surface)
    {
        surface_ = surface;
    }

    void set_active_tool(booba::Tool *tool)
    {
        create_memento(surface_);

        size_t current_tool = -1;

        for (size_t i = 0; i < tools_.size(); i++)
        {
            if (tools_[i] == tool)
            {
                current_tool = i;
                break;   
            }
        }

        active_tool_    = tool;

        std::vector<Widget *> setting_field_children = setting_field_->get_children();

        for (size_t i = 0; i < setting_field_children.size(); i++)
        {
            setting_field_->remove(setting_field_children[i]);
        }
    
        setting_field_->add(setting_palettes_[current_tool]);
    }

    booba::Tool *get_active_tool(booba::Tool *tool)
    {
        return active_tool_;
    }

    ~ToolManager() {};

protected:
    static std::deque<Memento *> mementoList_;
    static int numCommands_;
    static int max_forward_;
    static const int max_backup_ = MAX_BACKUP;

    friend class Canvas;
};

