#ifndef RECT_H
#define RECT_H


#include "mymath.h"
#include "vector2.h"


template <typename T>
struct rect
{
	rect() { }
	rect(T x1, T y1, T x2, T y2) : AA(x1, y1), BB(x2, y2) { }
	rect(const vector2<T>& a, const vector2<T>& b) : AA(a), BB(b) { }
	rect(const rect<T>& r) : AA(r.AA), BB(r.BB) { }
	template <typename TT> rect(const rect<TT>& r) : AA(r.AA), BB(r.BB) { }

	static inline rect<T> bySize(T x, T y, T w, T h) { return rect<T>(x, y, x + w, y + h); }
	static inline rect<T> byCenter(T cx, T cy, T w, T h) { return rect<T>(cx - w/2, cy - h/2, cx + w/2, cy + h/2); }
	static inline rect<T> byNullCenter(const vector2<T> &v) { return rect<T>(-v.x/2, -v.y/2, v.x/2, v.y/2); }

	void set(T x1, T y1, T x2, T y2) { AA.set(x1, y1); BB.set(x2, y2); }
	void set(const vector2<T>& a, const vector2<T>& b) { AA = a; BB= b; }
	void setBySize(T x, T y, T w, T h) { set(x, y, x + w, y + h); }
	void setByCenter(T cx, T cy, T w, T h) { set(cx - w/2, cy - h/2, cx + w/2, cy + h/2); }

	vector2<T> AA;
	vector2<T> BB;

	bool isPointInside(const vector2<T>& p) const
	{
		if (p.x < AA.x || p.y < AA.y || p.x > BB.x || p.y > BB.y)
			return false;
		return true;
	}

    void fixSize()
    {
        if (AA.x > BB.x) SWAP<float>(AA.x, BB.x);
        if (AA.y > BB.y) SWAP<float>(AA.y, BB.y);
    }

	vector2<T> getCenter() const { return vector2<T>((AA.x + BB.x) / 2, (AA.y + BB.y) / 2); }
	T getWidth() const { return fabs(AA.x - BB.x); }
	T getHeight() const { return fabs(AA.y - BB.y); }

	void translate(T dx, T dy) { AA.x += dx; AA.y += dy; BB.x += dx; BB.y += dy; }

	void clip(const rect& r) { if(AA.x<r.AA.x)AA.x=r.AA.x; if(AA.y<r.AA.y)AA.y=r.AA.y; if(BB.x>r.BB.x)BB.x=r.BB.x; if(BB.y>r.BB.y)BB.y=r.BB.y; }
};


typedef rect<int> recti;

typedef rect<float> rectf;


#endif // RECT_H
