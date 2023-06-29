#include <Game.hpp>
#include <Bird.hpp>
#include <Obstacle.hpp>
#include <thread>
#include <chrono>
#include <SFML/Audio.hpp>
#include <string>

namespace mt
{
	void Game::Setup(int m_Width, int m_Height, const std::string& m_caption) {			//�������� ����
		m_window = new sf::RenderWindow(sf::VideoMode(m_Width, m_Height), m_caption);	//���� � ��������� �����������
		m_window->setFramerateLimit(60);}												//����������� FPS
	
	//�������� ������� 
	void Game::Run(float m_Width, float m_Height) {

		//FPS//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int fps = 0;																	//				
		int fps_count = 0;																//		
		sf::Font font; font.loadFromFile("assets//font_1.ttf");							//�����	 FPS
		sf::Text fps_text; fps_text.setFont(font); fps_text.setCharacterSize(20);		//�����	
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//����/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int score = 0;
		int best_score = 0;
		sf::Font font_score; font_score.loadFromFile("assets//font_1.ttf");
		sf::Text score_text; score_text.setFont(font_score); score_text.setCharacterSize(20);
		score_text.setPosition(0,20);
		sf::Text best_score_text; best_score_text.setFont(font_score); best_score_text.setCharacterSize(20);
		best_score_text.setPosition(0, 40);
		sf::Font font_score_in_the_end; font_score_in_the_end.loadFromFile("assets//font_2.otf");
		sf::Text score_text_in_the_end; score_text_in_the_end.setFont(font_score_in_the_end); score_text_in_the_end.setCharacterSize(50);
		score_text_in_the_end.setPosition(m_Width/6, m_Height/8);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//��������� �������
		sf::Text start_text; start_text.setFont(font_score); start_text.setCharacterSize(30);

		//�������� �����///////////////////////////////////////////////////////////////////////////////////////////////////
		mt::Bird* Bird = new mt::Bird();												//��� ������
		Bird->Setup(0.25);																//��� ��������� ����� �������
		Bird->Spawn({ 200,252 });														//��������� ������������ 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//�������//////////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<mt::Column*> Columns;												//������ � ���������
		mt::Column* Column1 = new mt::Column();
		Column1->Setup_Column_Top				(0.25,{m_Width,10});
		Columns.push_back(Column1);

		mt::Column* Column2 = new mt::Column();
		Column2->Setup_Column_Bottom			(0.25,{m_Width,m_Height-10});
		Columns.push_back(Column2);

		mt::Column* Column3 = new mt::Column();
		Column3->Setup_Column_Top				(0.25,{m_Width+m_Width/4,10});
		Columns.push_back(Column3);

		mt::Column* Column4 = new mt::Column();
		Column4->Setup_Column_Bottom			(0.25,{m_Width+m_Width/4,m_Height-10});
		Columns.push_back(Column4);

		mt::Column* Column5 = new mt::Column();
		Column5->Setup_Column_Top				(0.25,{m_Width+2*m_Width/4,10});
		Columns.push_back(Column5);

		mt::Column* Column6 = new mt::Column();
		Column6->Setup_Column_Bottom			(0.25,{m_Width+2*m_Width/4,m_Height-10});
		Columns.push_back(Column6);

		mt::Column* Column7 = new mt::Column();
		Column7->Setup_Column_Top				(0.25,{m_Width+3*m_Width/4,10});
		Columns.push_back(Column7);

		mt::Column* Column8 = new mt::Column();
		Column8->Setup_Column_Bottom			(0.25,{m_Width+3*m_Width/4,m_Height-10});
		Columns.push_back(Column8);

		mt::Column* Column9 = new mt::Column();
		Column9->Setup_Column_Top				(0.25,{m_Width+4*m_Width/4,10});
		Columns.push_back(Column9);

		mt::Column* Column10 = new mt::Column();
		Column10->Setup_Column_Bottom			(0.25,{m_Width+4*m_Width/4,m_Height-10});
		Columns.push_back(Column10);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
		sf::Texture background_texture;	background_texture.loadFromFile("assets//background.png");
		sf::Sprite background; background.setTexture(background_texture);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//�������� ����////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool bird_is_alive = true;
		bool start = false;
		m_timer.restart();
		while (m_window->isOpen()) 
		{	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {start=true;m_timer.restart();} //�����
			if (start){
				//FPS - ��������///////////////////////////////////////////////////////////////////////////////////////////////////
				sf::Time elapsed = timer_fps.getElapsedTime();								//������ ���������� �������
				if (elapsed.asMilliseconds() >= 1000)										//���� ������ �������, �� 
				{																			//
					fps = fps_count;														//fps=fps_count 
					fps_count = 0;															//�������� �������
					timer_fps.restart();													//�������� ������
				}
				fps_text.setString("FPS: " + std::to_string(fps));;							//��������������� �������� � ������
				fps_count++;																//���������� �������
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//���� ��������� ������� �������///////////////////////////////////////////////////////////////////////////////////
				sf::Event event;
				while (m_window->pollEvent(event)) if (event.type == sf::Event::Closed) m_window->close();
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if (bird_is_alive) {
					bool bird_up_or_down = false;
					//�����////////////////////////////////////////////////////////////////////////////////////////////////////////
					Point p = Bird->GetPosition();
					float Bird_Ry = Bird->RadiusY(); float Bird_Rx = Bird->RadiusX();

					sf::Time deltaTime = m_timer.restart();											//�������� ����� ���������� �����

					if (p.y - Bird_Ry > 0)//�����
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
							Bird->UP(deltaTime.asSeconds());bird_up_or_down = true;}

					if (p.y + Bird_Ry <= m_Height)//����
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
							Bird->DOWN(deltaTime.asSeconds()); bird_up_or_down = true;}

					if(!bird_up_or_down) Bird->Zero_rotation();
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//�������///////////////////////////////////////////////////////////////////////////////////////////////////////
					int Random_Height = rand() % 100;												//��������� �����

					for (int i = 0; i < Columns.size(); i += 2) {									//�������� ������
						Point_c p_c = Columns[i]->GetPosition_c();									//����� ������ ������ �������
						float R_c_x = Columns[i]->RadiusX_c();										//������ �� ������ �� ���� 
						if (m_Width <= p_c.x - R_c_x) {												//���� ������� �� ������ ����� ������
							Columns[i]->Random_Shift_Top(m_Height, Random_Height, Bird_Ry);			//��������� ��������� ������
							Columns[i + 1]->Random_Shift_Bottom(m_Height, Random_Height);			//	
						}
						if (0 >= p_c.x + R_c_x) {													//������� ������ ����� ����� �� ����� ����
							Columns[i]->Restart(m_Width);											//
							Columns[i + 1]->Restart(m_Width);										//

						}
						Columns[i]->Columns_move(deltaTime.asSeconds());							//�������� ������� �������
						Columns[i + 1]->Columns_move(deltaTime.asSeconds());						//�������� ������ �������
						float R_c_y = Columns[i]->RadiusY_c();
						if (p_c.x - R_c_x <= p.x + Bird_Rx) { 										//�������������� � ��������� �� Ox
							if (p_c.x + R_c_x >= p.x + Bird_Rx) {									//
								if (p_c.y + R_c_y >= p.y - Bird_Ry) {								//�������������� ����� � ������� ������� �� Oy
									bird_is_alive = false;
								}
								if (p_c.y + R_c_y + 20 + 2 * Bird_Ry <= p.y + Bird_Ry) {			//�������������� ����� � ������ ������� �� Oy
									bird_is_alive = false;
								}
							}
							else if (p_c.x + R_c_x <= p.x - Bird_Rx)
								if (p_c.x + R_c_x + 95*deltaTime.asSeconds() >= p.x - Bird_Rx)
									score += 1;
						}
						score_text.setString("SCORE: " + std::to_string(score));
						if (score > best_score) best_score = score;
						best_score_text.setString("BEST SCORE: " + std::to_string(best_score));
						score_text_in_the_end.setString("YOUR SCORE: " + std::to_string(score) + "\n" + "BEST SCORE: " +std::to_string(best_score));
					}
				}
			}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				m_window->clear();																//������� ����� ��������������
				//���������////////////////////////////////////////////////////////////////////////////////////////////////////
				m_window->draw(background);														//����� ����

				if (!start) { 																	//��������� �����
					start_text.setPosition(80, 152);
					start_text.setString("PRESS SPACE TO START");
					m_window->draw(start_text);
				}
				if (bird_is_alive) {															//���� ����� ����
					for (int i = 0; i < Columns.size(); i++)									//����� ������
						m_window->draw(*Columns[i]->Get());										//
					m_window->draw(*Bird->Get());												//����� �����
					m_window->draw(fps_text);													//����� FPS
					m_window->draw(score_text);													//����� �����
					m_window->draw(best_score_text);
				}
				if (!bird_is_alive) {															//��������� ����
					m_window->draw(score_text_in_the_end);
					start_text.setPosition(m_Width / 2.5 , m_Height / 8 + 100);
					start_text.setString("PRESS R TO RESPAWN");
					m_window->draw(start_text);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {							//������� ������
						for (int i = 0; i < 1; i++) {
							Columns[i]->Restart_2(m_Width, i);
							Columns[i+1]->Restart_2(m_Width, i);
						}
						for (int i = 2; i < 3; i++) {
							Columns[i]->Restart_2(m_Width, i-1);
							Columns[i+1]->Restart_2(m_Width, i-1);
						}
						for (int i = 4; i < 5; i++) {
							Columns[i]->Restart_2(m_Width, i-2);
							Columns[i + 1]->Restart_2(m_Width, i-2);
						}
						for (int i = 6; i < 7; i++) {
							Columns[i]->Restart_2(m_Width, i - 3);
							Columns[i + 1]->Restart_2(m_Width, i - 3);
						}
						for (int i = 8; i < 9; i++) {
							Columns[i]->Restart_2(m_Width, i - 4);
							Columns[i + 1]->Restart_2(m_Width, i - 4);
						}
						score = 0;
						Bird->Spawn({ 200,252 });
						bird_is_alive = true;
						m_timer.restart();
						}
					}
				//�����������
				m_window->display();															
		}
		//�������� ��������� ��� ������� ������ 
		delete Bird;
		for (int i = 0; i < Columns.size(); i++)
			delete Columns[i];
	};
}