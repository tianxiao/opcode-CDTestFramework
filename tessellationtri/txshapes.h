#pragma once

template<typename T>
class txShpere
{
public:
	txShpere(T radius, size_t refinement_level, bool is_solid_inside);
	~txShpere(void);

	void TessellateSolid();

private:
	T radius;
	size_t refinement_level;
	bool is_solid_inside;
};

template<typename T>
txShpere<T>::txShpere(T radius, size_t refinement_level, bool is_solid_inside)
{
}

template<typename T>
txShpere<T>::~txShpere(void)
{
}

