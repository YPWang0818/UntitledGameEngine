#pragma once
#include "ugepch.h"
#include "glm/vec2.hpp"

 namespace UGE {

     class UGE_API InputHandler {


     public:
         inline static InputHandler& getInputHandler() {
             return *s_instance;
         };

         void operator=(const InputHandler&) = delete;

         inline static bool isKeyDown(int key) {
             return s_instance->_impel_is_key_down(key);
         };

         inline static bool isMouseButtonDown(int button) {
             return s_instance->_impel_is_mouse_button_down(button);
         };

         
         inline static glm::vec2 getCursorPos() {
             return s_instance->_impel_get_cursor_pos();
         };

     protected:
         virtual bool _impel_is_key_down(int key) = 0;
         virtual bool _impel_is_mouse_button_down(int button) = 0;
         virtual glm::vec2 _impel_get_cursor_pos() = 0;

     private:

            static std::shared_ptr<InputHandler> s_instance;

    };
}