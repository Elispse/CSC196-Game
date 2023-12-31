#include "Scene.h"

namespace Jackster
{
	void Scene::Update(float dt)
	{
		//remove destroyed actors
		auto iter = m_actors.begin();

		while (iter != m_actors.end())
		{
			(*iter)->Update(dt);

			if (iter->get()->m_destroyed)
			{
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
		//check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++)
			{
				float distance = (*iter1)->m_transform.position.distance((*iter2)->m_transform.position);
				float radius = (*iter1)->getRadius() + (*iter2)->getRadius();
				if (distance <= radius)
				{
					(*iter1)->onCollision(iter2->get());
					(*iter2)->onCollision(iter1->get());
					//boom

				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
	
}