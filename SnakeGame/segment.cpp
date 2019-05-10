#include "segment.h"

Segment::Segment(sf::Vector2f newPosition): position(newPosition)
{
	m_sNext = nullptr; //0 in text
}

Segment * Segment::getNext() const
{
	return m_sNext;
}

void Segment::setNext(Segment * next)
{
	m_sNext = next;
}

Segment * Segment::getPrevious() const
{
	return m_sPrev;
}

void Segment::setPrevious(Segment * prev)
{
	m_sPrev = prev;
}

void Segment::setPositionY(const float & newPos)
{
	position.y = newPos;
}

sf::Vector2f Segment::getPosition()
{
	return position;
}
