#include "hander.h"

namespace FCT {
	void CircleGeometry::traversal(void(*drawpoint)(void* param, int x, int y), void* param, int cx, int cy)
	{
		for (int x = 0,
			y = r,
			d = 1 - r //d的初始值
			; x < y; x++) {

			//下
			//drawpoint(param, cx + x, cy + y);
			//drawpoint(param, cx - x, cy + y);
			for (int i = cx - x; i <= cx + x; i++) {
				drawpoint(param, i, cy + y);
			}
			//中下
			//drawpoint(param, cx + y, cy + x);
			//drawpoint(param, cx - y, cy + x);
			for (int i = cx - y; i <= cx + y; i++) {
				drawpoint(param, i, cy + x);
			}
			//中上
			//drawpoint(param, cx + y, cy - x);
			//drawpoint(param, cx - y, cy - x);
			for (int i = cx - y; i <= cx + y; i++) {
				drawpoint(param, i, cy - x);
			}
			//上
			//drawpoint(param, cx + x, cy - y);
			//drawpoint(param, cx - x, cy - y);
			for (int i = cx - x; i <= cx + x; i++) {
				drawpoint(param, i, cy - y);
			}
			if (d <= 0) {
				d += 2 * x + 3;
				continue;
			}
			d += 2 * (x - y) + 5;
			y -= 1;
		}
	}

	void RectangleGeometry::traversal(void(*func)(void* param, int x, int y), void* param, int cx, int cy)
	{
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				func(param, cx + i, cy + j);
			}
		}
	}
	void EllipseGeometry::traversal(void(*func)(void* param, int x, int y), void* param, int cx, int cy)
	{
		if (cx > cy) {

			return;
		}


	}
}

