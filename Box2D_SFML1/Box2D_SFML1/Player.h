#pragma once
#ifndef _PLAYER_H__
#define _PLAYER_H__
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include<iostream>
#include <map>
#include <list>
#include<fstream>
#include "AudioManager.h"
#include "TextureMaster.h"
#include "Projectile.h"
#include "Staff.h"
#include "ParticleSystem.h"


class Player
{
public:
	Player(sf::RenderWindow* _renderWindow, b2World& _world, const float& _scale, AudioManager* _audiomanager);
	~Player();

	void Start();
	void Update(sf::Vector2f _mousepos);
	void Render();
	void PollMovement(sf::Event& _event);
	void Movement();
	void AddItemToInventory(Item* _item, bool _bCanStack = true);
	void AddItemToInventory(Item* _item, int _amount, bool _bCanStack = true);
	bool IsItemInInventory(Item* _item);
	bool IsItemInInventory(Item* _item, int _amount);
	void RemoveItemFromInventory(int _pos);
	void CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor = false);
	void DestroyBody();
	b2Body* GetBody();
	void SetMana(float _mana);
	float GetMana();
	void SetHealth(float _health);
	float GetHealth();
	void Attack(Projectile::PROJECTILETYPE _type);
	sf::Sprite GetShape();

	std::map<int, Item> m_Inventory;
	float m_iMovementSpeed = 50;
	std::list<Projectile> m_Projectiles;
	std::map<int, int> m_InventoryStackValues;
	int m_CurrentItemIndex = 0;

private:
	
	sf::RenderWindow* m_RenderWindow;

	sf::Clock m_ManaRegen;
	float m_ManaRegenFrequency = 1.f;
	float m_Mana = 100.f;
	float m_MaxMana = 100.f;
	float m_Health = 100.f;
	float m_MaxHealth = 100.f;
	float m_JumpForce = 500.0f;
	int m_InventorySize = -1;
	bool m_bCanJump = false;
	ParticleSystem* m_ParticleSystem;
	sf::Clock m_ParticleClock;
	b2Vec2 m_Velocity;
	sf::Texture m_PlayerTexture;
	sf::Sprite m_Shape;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body;
	b2World* m_World;
	AudioManager* m_AudioManager;
	Projectile* m_Projectile;
	Staff* m_Staff;
	sf::Clock m_AttackTimer;
	sf::Vector2f m_MousePos;

	float m_Scale;
};

#endif