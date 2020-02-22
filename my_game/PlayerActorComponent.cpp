#include "PlayerActorComponent.hpp"

#include <gamelib_locator.hpp>
#include <gamelib_random.hpp>
#include <limits>

namespace GameLib {
	extern void debugDraw(Actor& a);
	extern void debugDrawSweptAABB(Actor& a);
	extern float SweptAABB(Actor& a, Actor& b, glm::vec3& normal);


	void PlayerActorComponent::update(Actor& a, World& w) {
		// debugDraw(a);
		// debugDrawSweptAABB(a);
		health-=0.5*a.dt;
		HFLOGDEBUG("Health: %f",health );
		if(health<=0){
			a.active=false;

		}
		if (a.isTrigger()) {
			if (triggerInfo.t > 0.0f) {
				a.position.y = triggerInfo.position.y + std::sin(50.0f * triggerInfo.t) * 0.25f;
				triggerInfo.t -= a.dt;
				if (triggerInfo.t < 0.0f) {
					a.position = triggerInfo.position;
					a.anim.baseId = a.spriteId();
				}
			}
		}
	}


	void PlayerActorComponent::beginPlay(Actor& a) {
		if (a.isStatic()) {
			staticInfo.horizontal = (random.rd() & 1) == 1;
			staticInfo.movement = random.positive() * 5.0f + 2.0f;
			staticInfo.position = a.position;
		}
	}


	void PlayerActorComponent::handleCollisionStatic(Actor& a, Actor& b) {
		return;
	}


	void PlayerActorComponent::handleCollisionDynamic(Actor& a, Actor& b) {
		return;
	}


	void PlayerActorComponent::handleCollisionWorld(Actor& a, World& w) {
		return;
	}


	void PlayerActorComponent::beginOverlap(Actor& a, Actor& b) {
		health+=20;
		HFLOGDEBUG("Actor '%d' is now overlapping trigger actor '%d'", a.getId(), b.getId());
		HFLOGDEBUG("Health: %f",health );
	}


	void PlayerActorComponent::endOverlap(Actor& a, Actor& b) {
		HFLOGDEBUG("Actor '%d' is not overlapping trigger actor '%d'", a.getId(), b.getId());
	}

	void PlayerActorComponent::beginTriggerOverlap(Actor& a, Actor& b) {
		HFLOGDEBUG("Trigger actor '%d' is now overlapped by actor '%d'", a.getId(), b.getId());
		if (triggerInfo.t <= 0.0f) {
			// if we are not already animating
			a.anim.baseId = a.spriteId() + 50;
		}
		triggerInfo.position = a.position;
		triggerInfo.t = 2.0f;
		b.position.x = 1 + random.positive() * (Locator::getWorld()->worldSizeX - 2);
		b.position.y = 1 + random.positive() * (Locator::getWorld()->worldSizeY - 2);
		Locator::getAudio()->playAudio(1, true);
	}


	void PlayerActorComponent::endTriggerOverlap(Actor& a, Actor& b) {
		HFLOGDEBUG("Trigger actor '%d' is not overlapped by actor '%d'", a.getId(), b.getId());
	}
} // namespace GameLib
