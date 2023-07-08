#pragma once
#include "component.h"
#include <list>
class GameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	std::list<Component*> m_Component;

public:
	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}

	}

	void SetPosition(D3DXVECTOR3 Position){m_Position = Position;}
	void SetVelocity(D3DXVECTOR3 velocity) { m_Position = +velocity; }

	void SetScale(D3DXVECTOR3 Scale){m_Scale = Scale;}
	D3DXVECTOR3 GetPosition(){return m_Position;}
	D3DXVECTOR3 GetScale (){return m_Scale;}

	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	virtual void Init(){}//‰¼‘zŠÖ”
	virtual void Uninit()
	{

		for (Component* Component : m_Component)
		{
			Component->Uninit();
			delete Component;
		}
		m_Component.clear();
	}
	virtual void Update()
	{
		for (Component* Component : m_Component)
		{
			Component->Update();
		}
	}
	virtual void Draw()
	{
		for (Component* Component : m_Component)
		{
			Component->Draw();
		}
	}

	template <typename T>
	T* AddComponent()
	{
		Component* component = new T();
		m_Component.push_back(component);
		component->Init();

		return (T*)component;
	}

};