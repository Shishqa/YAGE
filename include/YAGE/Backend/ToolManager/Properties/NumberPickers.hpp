/*============================================================================*/
#ifndef YAGE_NUMBERPICKERS_HPP
#define YAGE_NUMBERPICKERS_HPP
/*============================================================================*/
#include "Slidable.hpp"
#include "Stroke.hpp"
/*============================================================================*/
namespace YAGE {

    class PropSlider : public Sh::Slidable {
    public:

        explicit PropSlider(Sh::UIWindow* target, const Sh::Frame& frame,
                            Property* to_track)
                : Sh::Slidable(target, frame)
                , prop(to_track)
                , is_locked(false) {
            Sh::SubscriptionManager::subscribe<PropUpdateEvent>(this, to_track);
        }

        virtual void onPropUpdate() = 0;

        virtual void modifyProp(const Sh::Vector2<double>& pos) = 0;

        void onSlide(const Sh::Vector2<double>& pos) final {
            if (!is_locked) {
                is_locked = true;
                modifyProp(pos);
                is_locked = false;
            }
        }

        bool onEvent(Sh::Event& event) override {

            if (event.mask() != Sh::Event::getMask<PropUpdateEvent>()) {
                return false;
            }

            auto prop_update = dynamic_cast<PropUpdateEvent&>(event);

            if (prop_update.updated() == prop && !is_locked) {
                is_locked = true;
                onPropUpdate();
                is_locked = false;
                return true;
            }

            return false;
        }

    protected:

        template <typename Prop>
        Prop* getProp() {
            return dynamic_cast<Prop*>(prop);
        }

    private:

        Property* prop;
        bool is_locked;
    };


    class FloatingPropPicker : public PropSlider {
    public:

        explicit FloatingPropPicker(Sh::UIWindow* target, const Sh::Frame& frame,
                                    FloatingPointProp* to_track)
                : PropSlider(target, frame, to_track)
                { }

        void modifyProp(const Sh::Vector2<double> &pos) override {
            getProp<FloatingPointProp>()->setValue(pos.x);
        }

        void onPropUpdate() override {
            set({getProp<FloatingPointProp>()->getValue(), 0});
        }

    };

    class IntPropPicker : public PropSlider {
    public:

        static constexpr double MAX_VALUE = 100.0;

        explicit IntPropPicker(Sh::UIWindow* target, const Sh::Frame& frame,
                               IntProp* to_track)
            : PropSlider(target, frame, to_track)
            { }

        void modifyProp(const Sh::Vector2<double> &pos) override {
            getProp<IntProp>()->setValue(static_cast<int32_t>(pos.x * MAX_VALUE));
        }

        void onPropUpdate() override {
            set({static_cast<double>(getProp<IntProp>()->getValue()) / MAX_VALUE, 0});
        }

    };

}
/*============================================================================*/
#endif //YAGE_NUMBERPICKERS_HPP
/*============================================================================*/