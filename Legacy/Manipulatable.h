//#pragma once
//#include "Drawable.h"
//
//class Manipulatable : public Visible
//{
//public:
//	//Update methods
//	void draw(SDL_Renderer* mRenderer);
//
//	void setRotation(double aRotation);
//
//	void rotate(double aRotation);
//
//	//Constructors
//	Manipulatable(SDL_Texture* texture);
//
//	Manipulatable(SDL_Texture* texture, SDL_RendererFlip aFlip, double aRotation, SDL_Point aPoint);
//
//	Manipulatable(pugi::xml_node node, std::vector<Drawable*>* drawVector);
//
//private:
//	double rotation;
//	SDL_RendererFlip flip;
//	SDL_Point point;
//};