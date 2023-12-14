#pragma once
#include <iostream>
#include <thread>
#include <algorithm>
#include <random>
#include <limits>
#include <fstream>
#include "Barrier.h"
#include "Rayon.h"
#include "Vec3D.h"
#include "Scene.h"


namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

// Job concret : exemple


class SleepJobBarrier : public Job {
	int calcul (int v) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		std::this_thread::sleep_for(std::chrono::seconds(1));
		int ret = v % 255;
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		return ret;
	}
	int arg;
	int * ret;
	Barrier* bar;
public :
	SleepJobBarrier(int arg, int * ret, Barrier* bar) : arg(arg), ret(ret),  bar(bar){}
	void run () {
		* ret = calcul(arg);
		bar->done();
	}
	~SleepJobBarrier(){}
};

class DrawJobBarrier : public Job {
	int foo(int v) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return (v % 255) ;
	}
	const Vec3D & screenPoint;
	Color & pixel;
	const Scene & scene;
	const std::vector<Vec3D> & lights;
	Barrier* bar;
public :
	DrawJobBarrier(const Vec3D & screenPoint, Color & pixel, const Scene & scene, const std::vector<Vec3D> &lights, Barrier* bar) : screenPoint(screenPoint), pixel(pixel), scene(scene), lights(lights), bar(bar) {}

	void run() {
		Rayon ray(scene.getCameraPos(),screenPoint);
		Color finalcolor;
		auto min = std::numeric_limits<float>::max();
		for (const auto & obj : scene) {
			auto mizinter = obj.intersects(ray);
			if (mizinter < min){
				min = mizinter;
				finalcolor= obj.getColor();

				auto camera = scene.getCameraPos();

				Vec3D rayInter  = (ray.dest - ray.ori).normalize() * mizinter;
				Vec3D intersection = rayInter + camera;
				Vec3D normal = obj.getNormale(intersection);

				double dt = 0;

				for(const auto & light : lights){
					Vec3D tolight = (light - intersection);
					if(obj.intersects(Rayon(light,intersection))>= tolight.length() -0.05){
						dt += tolight.normalize() & normal;
					}
				}

				finalcolor = finalcolor*dt + finalcolor *0.2 ; 
			}
		}
		pixel = finalcolor;
		bar->done();
	}

	~DrawJobBarrier() {}
};

}
