#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class RecordLayer : public geode::Popup<> {
    public:
        bool setup() override;
        static RecordLayer* create();

        void onRecord(CCObject*);
};