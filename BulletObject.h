#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H


#include "BaseObject.h"
#include "CommonFunc.h"

class BulletObject : public BaseObject
{
public : 
	BulletObject(); 
	~BulletObject();

	enum BulletDir {
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
	};

	void set_x_val(const int& xVal) { x_val = xVal; }
	void set_y_val(const int& yVal) { y_val = yVal; }
	int get_x_val() const { return x_val; }
	int get_y_val() const { return y_val;  }


	void set_is_move(const bool& isMove) { is_move = isMove; }
	bool get_is_move() const { return is_move; }

	void HandleMove(const int& x_border, const int& y_border);
	void set_bullet_dir(const int& bulletDir) { bullet_dir = bulletDir; }
	int get_bullet_dir() const{ return bullet_dir; }

private: 
	int x_val, y_val;
	bool is_move;  // tr?ng thái xem ??n có ?ang ? trong màn hình không
    int bullet_dir; 
	
};


#endif 

