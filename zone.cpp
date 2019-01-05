#include "zone.h"

Zone::Zone()
{
  isMine = false;
  isRevealed = false;
  isFlagged = false;
  value = 0;
  x = -1;
  y = -1;
}

Zone::~Zone()
{  }

bool Zone::getMineStatus()
{
  return isMine;
}

void Zone::setMineStatus(bool s)
{
  isMine = s;
}

bool Zone::getRevealedStatus()
{
  return isRevealed;
}

void Zone::setRevealedStatus(bool s)
{
  isRevealed = s;
}

bool Zone::getFlaggedStatus()
{
  return isFlagged;
}

void Zone::setFlaggedStatus(bool s)
{
  isFlagged = s;
}

int Zone::getValue()
{
  return value;
}

void Zone::setValue(int v)
{
  value = v;
}

int Zone::getX()
{
  return x;
}

void Zone::setX(int X)
{
  x = X;
}

int Zone::getY()
{
  return y;
}

void Zone::setY(int Y)
{
  y = Y;
}
