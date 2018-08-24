#ifndef _KD_TREE_
#define _KD_TREE_

#include "num_vector.h"
namespace algo {

	template<size_t _Size>
	class Rect {
	public:
		typedef NumVector<double, _Size> Vec;
		Rect(vec rmin, vec rmax);
		Rect(const Rect& other);
		Rect& operator=(const Rect& other);
		~Rect();
		bool operator!=(const Rect& other);
		bool operator==(const Rect& other);
		const Vec min() const;
		const Vec max() const;
		bool intersects(const Rect& other);
		bool contains(const Vec& point);
		double distanceTo(const Vec& point);
		Vec absDistanceVectorTo(const Vec& point);
		double volume() const;
	private:
		Vec r_min, r_max;
	};

	template<class _Type, size_t _Size>
	class KdTree {
	public:
		typedef NumVector<double, _Size> Point;
		typedef Rect<_Size> Rec;
		struct Node {
			Point	point_;
			_Type	val_;
			Node*	left_;
			Node*	right_;
			size_t	axis_;
			size_t	size_;
			Rec		rec_;
			Node(Point point, _Type val, Rec rec, size_t axis, size_t size) {
				point_ = point; val_ = val;
				left = nullptr; right = nullptr;
				axis_ = axis; size_ = size;
				rec_ = rec;
			}
			~Node() {}
			double compare(const Point& point) const {
				return point_[axis_] - point[axis_];
			}

			double compare(const Node& node, size_t axis) const {
				return this->point_[axis] - node.point_[axis];
			}

			double compare(Node* node, size_t axis) const {
				return this->point_[axis] - node->point_[axis];
			}

			Rec getLeftRect() const {
				Point lmin = rec_.min();
				Point lmax = rec_.max();
				lmax[axis_] = point_[axis_];
				return Rec(lmin, lmax);
			}

			Rec getRightRect() const {
				Point rmin = rec_.min();
				Point rmax = rec_.max();
				rmin[axis_] = point_[axis_];
				return Rec(rmin, rmax);
			}
		}; 

		bool isEmpty() const;
		size_t size() const;

	private:
		Node * root;
		size_t size(Node* node);
	};

}

#endif // !_KD_TREE_

