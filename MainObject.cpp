﻿

#include "MainObject.h"

MainObject::MainObject() {
	frame = 0;
	x_pos = 500;
	y_pos = 60;
	x_val = 0; 
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status = -1; 
	input_type.left = 0;
	input_type.right = 0;
	input_type.down = 0;
	input_type.up = 0;
}

MainObject :: ~MainObject() {

}


bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true) {
		width_frame = rect.w / 8;
		height_frame = rect.h ;    // chu y : height_frame = 45 , width_frame = 40 ; 
	}
	return ret; 
}

void MainObject::set_clips() {                         
	if (width_frame > 0 && height_frame > 0) {

		for (int i = 0; i <= 7; i++) {
			frame_clip[i].x = i * width_frame; 
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame; 
		}
	}
}

void MainObject::Show(SDL_Renderer* des) {
	if (status == WALK_LEFT) {
		LoadImg("map1/player_left.png", des);  // ham LoadImg nay la ham trong MainObject.h chu kp trong Object.h
	}
	else{
		LoadImg("map1/player_right.png",des);
	}
	if (input_type.left == 1 || input_type.right == 1) {
		frame++;
	}
	else {
		frame = 0;
	}

	if (frame >= 8) {
		frame = 0;
	}

	rect.x = x_pos;  // day la vi tri tren man hinh ma hien thi nhan vat len
	rect.y = y_pos; 

	SDL_Rect* current_clip = &frame_clip[frame];

	SDL_Rect renderQuad = { rect.x ,rect.y , width_frame ,height_frame };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}


void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym)
		{
			case SDLK_RIGHT: 
			{
				status = WALK_RIGHT; 
				input_type.right = 1;
				input_type.left = 0;
				input_type.up = 0;
				input_type.down = 0;
				break; 
			}
			case SDLK_LEFT:
			{
				status = WALK_LEFT; 
				input_type.left = 1;
				input_type.right = 0;
				input_type.up = 0;
				input_type.down = 0;

				break; 
			}
			case SDLK_UP:
			{
				status = WALK_UP; 
				input_type.up = 1;
				input_type.right = 0; 
				input_type.left = 0; 
				input_type.down = 0;
				break; 
			}
			case SDLK_DOWN:
			{
				status = WALK_DOWN; 
				input_type.down = 1;
				input_type.up = 0;
				input_type.left = 0;
				input_type.right = 0;
				break;
			}
		}
	}
	else if (events.type ==SDL_KEYUP)  
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_RIGHT:
			{
			input_type.right = 0;
			break;
			}

			case SDLK_LEFT:
			{
			input_type.left = 0;
			break;
			}
			case SDLK_UP:
			{
				input_type.up = 0;
				break;
			}
			case SDLK_DOWN:
			{
				input_type.down = 0;
				break;
			}
		}
	}
	// nhấn để bắn đạn 
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if (events.button.button == SDL_BUTTON_LEFT) {
			BulletObject* p_bullet = new BulletObject();
			p_bullet->LoadImg("map1/player_bullet.png", screen);

			if (status == WALK_LEFT) {
				p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
				p_bullet->SetRect(this->rect.x -20 , rect.y + 0.25 * height_frame);
			}

			else if (status == WALK_RIGHT)
			{
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
				p_bullet->SetRect(this->rect.x + width_frame -20, rect.y + 0.25 * height_frame);
			}
			
			p_bullet->set_x_val(15);  // set tốc độ đạn 
			p_bullet->set_is_move(true); // chuyển sang true tức là cho phép đạn bắn ra 
			// nhu vậy phần trên đã khởi tạo xong viên đạn 


			bullet_list.push_back(p_bullet); // nạp đạn sẵn vào băng, chỉ ấn là đạn sẽ xuất hiện
		}
	}
}

// xử lý đạn 
void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list.size(); i++) {
		BulletObject* p_bullet = bullet_list.at(i);
		if (p_bullet != NULL) {
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else{
				bullet_list.erase(bullet_list.begin() + i);
				if (p_bullet != NULL) {
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}


void MainObject::DoPlayer(Map& map_data) {
	x_val = 0;
	y_val = 0;    
	if (input_type.left == 1) {
		x_val -= PLAYER_SPEED; 
	}
	else if (input_type.right == 1) {
		x_val += PLAYER_SPEED; 
	}
	if (input_type.down == 1) {
		y_val += PLAYER_SPEED;
	}
	else if (input_type.up == 1) {
		y_val -= PLAYER_SPEED;
	}
	CheckToMap(map_data);
}


void MainObject::CheckToMap(Map&map_data) {
	int map_x1, map_x2, map_y1, map_y2; 
	map_x1 = (x_pos +x_val -185) / TILE_SIZE;
	map_x2 = (x_pos + x_val + width_frame -185 -1 ) / TILE_SIZE; 
	map_y1 = (y_pos -15) / TILE_SIZE; 
	map_y2 = (y_pos + height_frame - 15 -1) / TILE_SIZE;
	if (map_x1 >= 0 && map_x2 < MAX_MAP_X && map_y1 >= 0 && map_y2 < MAX_MAP_Y)
	{
		if (x_val > 0) {
			// 15 la toa do y de set_rect cho cac o vuong dòng 0 
			if (map_data.tile[map_y1][map_x2] != BLANK_TILE || map_data.tile[map_y2][map_x2] != BLANK_TILE) {  
				x_pos = 185 + TILE_SIZE * (map_x2)-width_frame - 1; 
				x_val = 0;
			}
		}
		else if (x_val < 0) {

			if (map_data.tile[map_y1][map_x1] != BLANK_TILE || map_data.tile[map_y2][map_x1] != BLANK_TILE) {   
				x_pos = 185 + (map_x1 + 1) * TILE_SIZE; 
				x_val = 0;
			}
		}
	}
	 map_x1 = (x_pos - 185) / TILE_SIZE;
	 map_x2 = (x_pos + width_frame -185 -1) / TILE_SIZE; 
	 map_y1 = (y_pos + y_val -15) / TILE_SIZE;
	 map_y2 = (y_pos + y_val + height_frame -15 -1) / TILE_SIZE;
	 if (map_x1 >= 0 && map_x2 < MAX_MAP_X && map_y1 >= 0 && map_y2 < MAX_MAP_Y) {
		 if (y_val > 0) {
			 if (map_data.tile[map_y2][map_x1] != BLANK_TILE || map_data.tile[map_y2][map_x2] != BLANK_TILE) {
				 y_pos = 15 + map_y2 * TILE_SIZE - height_frame - 1;
				 y_val = 0;
			 }
		 }

		 else if (y_val < 0)
		 {
			 if (map_data.tile[map_y1][map_x1] != BLANK_TILE || map_data.tile[map_y1][map_x2] != BLANK_TILE)
			 {
				 y_pos = (map_y1 + 1) * TILE_SIZE + 15;
				 y_val = 0;
			 }
		 }
	 }

	 x_pos += x_val;
	 y_pos += y_val; 
	 if (x_pos < 185) {   
		 x_pos = 185;
	 }
	 else if (x_pos + width_frame > 185 + TILE_SIZE* (MAX_MAP_X) ) {
		 x_pos = 185 + TILE_SIZE * MAX_MAP_X - width_frame - 1 ;
	 }
}



