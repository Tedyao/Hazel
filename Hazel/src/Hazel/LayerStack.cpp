#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

	LayerStack::LayerStack()
	{
		m_insertLayer = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		m_insertLayer = m_Layers.emplace(m_insertLayer, layer);
		layer->onAttach();
	}

	void LayerStack::pushOverlay(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->onAttach();

	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);
			m_insertLayer--;
		}
	}

}