#pragma once
#include "Core.h"
#include "Layer.h"
#define ITERATOR std::vector<Layer*>::iterator

namespace Hazel {
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
		void popLayer(Layer* layer);
		inline ITERATOR begin() { return m_Layers.begin(); }
		inline ITERATOR end() { return m_Layers.end(); }
	private:
		ITERATOR m_insertLayer;
		std::vector<Layer*> m_Layers;


	};
}
