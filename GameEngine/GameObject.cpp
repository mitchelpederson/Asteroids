#include <algorithm>

#include "GameObject.h"
#include "Log.h"

using namespace std;

int GameObject::m_nextId = 0;


void GameObject::DoPreUpdate(const GameTime& time)
{
    OnPreUpdate(time);
    
    for (auto it = begin(m_children); it != end(m_children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPreUpdate(time);
    }
    
}

void GameObject::DoUpdate(const GameTime& time)
{
	if (enabled) {

		for (auto it = begin(m_children); it != end(m_children); ++it)
		{
			if (nullptr != *it)
				(*it)->DoUpdate(time);
		}

	}
    OnUpdate(time);
    
    
    
}

void GameObject::DoPostUpdate(const GameTime& time)
{
    
    for (auto it = begin(m_children); it != end(m_children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPostUpdate(time);
    }
    
    OnPostUpdate(time);
    
}

void GameObject::DoPreRender(const GameTime& time)
{
    OnPreRender(time);
    
    for (auto it = begin(m_children); it != end(m_children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPreRender(time);
    }
    
}

void GameObject::DoRender(const GameTime& time)
{
    check_gl_error();
    
	if (enabled) {

		OnRender(time);
    
		for (auto it = begin(m_children); it != end(m_children); ++it)
		{
			if (nullptr != *it)
				(*it)->DoRender(time);
		}
	}
    
}

void GameObject::DoPostRender(const GameTime& time)
{
    
    for (auto it = begin(m_children); it != end(m_children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPostRender(time);
    }
    
    OnPostRender(time);
    
}




void GameObject::Update(const GameTime& time)
{
	if (enabled) {

		DoPreUpdate(time);
		DoUpdate(time);
		DoPostUpdate(time);

	}
	else {
		DEBUG_BREAK;
	}
}

void GameObject::Render(const GameTime& time)
{
    check_gl_error();
	if (enabled) {

		DoPreRender(time);
		DoRender(time);
		DoPostRender(time);

	}

    
    check_gl_error();
}


bool GameObject::Initialize()
{
    auto result = OnInitialize();
    check_gl_error();
    
    for (auto it = begin(m_children); it != end(m_children); ++it)
    {
        result &= (*it)->Initialize();
    }
    
    return result;
}

void GameObject::Dispose()
{
    for(auto it = begin(m_children); it != end(m_children); ++it)
    {
        (*it)->Dispose();
        delete *it;
        *it = nullptr;
    }

    m_children.clear();
    
    OnDispose();
    
}

void GameObject::Enable() {
	enabled = true;
}

void GameObject::Disable() {
	enabled = false;
}














