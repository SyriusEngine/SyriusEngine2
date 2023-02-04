#pragma once

#include "Include.hpp"

namespace Syrius{

    class SR_API Layer{
    public:

        /**
         * @brief Default Destructor.
         */
        virtual ~Layer();

        /**
         * @brief Called when the layer is pushed onto the layer stack.
         */
        virtual void onAttach() = 0;

        /**
         * @brief Called when the layer is popped from the layer stack.
         */
        virtual void onDetach() = 0;

        /**
         * @brief This function should be used to perform some updates/state changes. This function is guaranteed to be
         *        called once per frame.
         */
        virtual void onUpdate() = 0;

        /**
         * @brief Events dispatched from the main window can be processed in this function. It is possible that this
         *        function is called multiple times per frame or none at all. This function can also be used to prevent
         *        events from travelling down the layer stack. events travel from top to bottom on the stack, so the order
         *        in which layers are processed can be important.
         * @param event Event from the window.
         * @return true if event should travel further down the stack, false otherwise.
         */
        virtual bool onEvent(const Event& event) = 0;

    protected:

        Layer();
    };

}