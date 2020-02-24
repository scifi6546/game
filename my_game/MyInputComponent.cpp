#include "pch.h"
#include <gamelib_locator.hpp>
#include <gamelib_random.hpp>
#include "MyInputComponent.hpp"

namespace GameLib {
	void MyInputComponent::update(Actor& actor) {
		auto axis1 = Locator::getInput()->axis1X;
		if (axis1)
			actor.velocity.x = axis1->getAmount()*10;
		//    actor.velocity.x = axis1->getAmount();
		auto axis2 = Locator::getInput()->axis1Y;
		if (axis2 && actor.jumped==false){
			actor.velocity.y = axis2->getAmount()*1000.0f;
            actor.jumped=true;
        }
		//    actor.velocity.y = axis2->getAmount();
	}

	
} // namespace GameLib
