#pragma once
#include "../Graphics/FrameBuffer.hpp"
#include "../Graphics/TextureData.hpp"

class Planet;
class Atmosphere;

class AtmoPreComputer : public Singleton<AtmoPreComputer>
{
public:
	//Separate from constructor so we can unload the resources if we don't need them anymore
	void Init();
	void Unload();

	void Precalculate( Atmosphere* atmo );

private:
	//Textures - probably also need fbos
	TextureData* m_TexDeltaIrradiance;
	TextureData* m_TexDeltaRayleigh;
	TextureData* m_TexDeltaMie;
	TextureData* m_TexDeltaScattering;

	ivec3 m_ScatteringTexDim;
	TextureParameters m_TexParams;

	//Precomputation Shaders
	ShaderData* m_pComputeTransmittance;
	ShaderData* m_pComputeDirectIrradiance;
	ShaderData* m_pComputeSingleScattering;
	ShaderData* m_pComputeScatteringDensity;
	ShaderData* m_pComputeIndirectIrradiance;
	ShaderData* m_pComputeMultipleScattering;

	//other
	int32 m_Step = 0;
	int32 m_Order = 0;

	bool m_IsInitialized = false;
	bool m_Finished = false;

private:
	friend class Singleton<AtmoPreComputer>;

	AtmoPreComputer();
	~AtmoPreComputer();
};

class Atmosphere
{
public:
	Atmosphere();
	~Atmosphere();

	void Precalculate();
	void Initialize();
	void Draw(Planet* pPlanet, float radius);

private:
	friend class AtmoPreComputer;

	//Camera and pos reconstruction from gbuffer
	GLint m_uMatModel;
	GLint m_uMatWVP;

	GLint m_uCamPos;
	GLint m_uProjA;
	GLint m_uProjB;
	GLint m_uViewProjInv;

	GLint m_uPosition;
	GLint m_uRadius;
	GLint m_uSurfaceRadius;

	//textures for precomputed data
	static const int TRANSMITTANCE_W = 256;
	static const int TRANSMITTANCE_H = 64;
	TextureData* m_TexTransmittance;

	static const int IRRADIANCE_W = 64;
	static const int IRRADIANCE_H = 16;
	TextureData* m_TexIrradiance;

	static const int INSCATTER_R = 32;
	static const int INSCATTER_MU = 128;
	static const int INSCATTER_MU_S = 32;
	static const int INSCATTER_NU = 8;
	TextureData* m_TexInscatter;

	ShaderData* m_pShader;
};

