#include "Component.h"

void Component::attach(Component *component) {
	mChildren.push_back(component);
}