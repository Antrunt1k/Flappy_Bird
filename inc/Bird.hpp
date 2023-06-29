#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace mt
{
	struct Point {float x, y;};	  //�����
	class Bird
	{
	private:
		sf::Texture* m_texture;			//��������
		sf::Sprite* m_bird = nullptr;	//������
		float m_scale;                  //�������
		float m_Rx;						//������ - x
		float m_Ry;						//������ - y
		Point m_p0;						//�����

	public:
		Bird() {}													//�����������

		bool Bird::Setup(float scale)
		{
			m_texture = new sf::Texture();							//�������� �������� �����
			if (!m_texture->loadFromFile("assets//bird.png"))		//
			{std::cout << "Error" << std::endl;return false;}		//
			m_bird = new sf::Sprite;								//�������� �������
			m_bird->setTexture(*m_texture);							//��������� �������� ��� �������
			float x = m_texture->getSize().x;
			float y = m_texture->getSize().y;
			m_scale = scale;
			m_bird->setScale(m_scale, m_scale);						//��������� ������� �������	
			m_bird->setOrigin(x / 2, y / 2);						//�������� ������� ��������� ������� � ��� �����
			m_Ry = m_texture->getSize().y * m_scale / 4;
			m_Rx = m_texture->getSize().x * m_scale / 4;

			return true;
		}
		sf::Sprite* Get() {return m_bird;}

		void Spawn(Point p0) {
			m_p0 = p0;
			m_bird->setPosition(m_p0.x, m_p0.y);					//��������� ��������� ������� �������
		}

		void DOWN(double deltaTime) {
			m_bird->setRotation(45.f);

			m_p0.y += 150*deltaTime;
			m_bird->setPosition(m_p0.x, m_p0.y);
;		}

		void UP(double deltaTime) {
			m_bird->setRotation(-45.f);								//������� �� 45 �������� ����� ��� �����

			m_p0.y -= 150 * deltaTime;					
			m_bird->setPosition(m_p0.x,m_p0.y );					//������ ��������� ������� �� y

		}

		void Zero_rotation() {m_bird->setRotation(0.f);}

		Point GetPosition() {
			Point y{m_p0.x, m_bird->getPosition().y};					//��������� ������� ������� ������ �������
			return y;
		}		
		float RadiusY() {return m_Ry;}								   //��������� ������� - y 
		float RadiusX() {return m_Rx;}                                 //��������� ������� - x
	};
}