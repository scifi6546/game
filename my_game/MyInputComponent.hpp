#ifndef MY_INPUT_COMPONENT_HPP
#define MY_INPUT_COMPONENT_HPP

#include <gamelib_actor.hpp>
#include <gamelib_input_component.hpp>

namespace GameLib {
    class MyInputComponent : public InputComponent {
    public:
        virtual ~MyInputComponent() {}
        void update(Actor& actor) override;
    };
}

#endif
