#ifndef SHAPES_H
#define SHAPES_H
#include "vec2.hpp"


struct ShapeDescriptor
{
	enum class Type { Box } type;

	union
	{
		struct { glm::vec2 size; } box;
	};
};

class Shape
{
public:
	virtual ~Shape() = default;

	virtual ShapeDescriptor GetDescriptor() const = 0;
};


class BoxShape : public Shape
{
public:
	BoxShape(float width, float height):
	m_Size(width, height)
	{
		assert(width > 0 || height > 0 && "BoxShape dimensions must be > 0");
	}

	BoxShape(glm::vec2 widthAndHeight) :
		m_Size(widthAndHeight)
	{
		assert(widthAndHeight.x > 0 || widthAndHeight.y > 0 && "BoxShape dimensions must be > 0");
	}

	virtual ~BoxShape() = default;

	ShapeDescriptor GetDescriptor() const override
	{
		return ShapeDescriptor{
			.type = ShapeDescriptor::Type::Box,
			.box = {.size = m_Size }
		};
	}

private:
	glm::vec2 m_Size;
};
#endif // SHAPES_H
