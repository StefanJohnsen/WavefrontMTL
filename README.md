# WavefrontMTL


Wavefront MTL Parser - C++ Class for Parsing Material Information

A header-only C++ wavefront material parser is a self-contained software component that can be included in C++ projects and is designed to parse and extract material properties from Wavefront Material Template Library (MTL) files. The parser operates solely on the material-related data in the MTL files, allowing for easy integration into C++ projects without the need for external dependencies. It can interpret and extract properties such as ambient color, diffuse color, specular color, shininess, transparency, and texture maps defined in the MTL file. The extracted material properties can then be used for tasks such as rendering realistic 3D objects in computer graphics applications.

The solution is self-contained in a single header file, making it easy to integrate into existing projects without the need for additional libraries or dependencies.

Key Features:

- Supports parsing of standard MTL parameters
- Supports parsing of Clara.io MTL parameters
- Supports parsing of DirectXMesh MTL parameters
- Retrieves header information and all materials in the MTL file
- Provides convenient access to material properties
- Robust and efficient parsing algorithm for handling large MTL files
- Suitable for integration into 3D graphics applications, game engines,
  and other computer graphics projects

## Material Class

After parsing the material file, you will be presented with a comprehensive list of all the materials that were discovered in the file. Each material is encapsulated within a struct and contains the following member variables.

| Member        | Type          | Description                  | Extension                              |
|---------------|---------------|------------------------------|----------------------------------------|
| name          | string        | Material name                |                                        |
| Kd            | Color         | Color                        |                                        |
| Ka            | Color         | Color Ambient                |                                        |
| Ks            | Color         | Color Specular               |                                        |
| Tf            | Color         | Color Transmission           |                                        |
| Ns            | double        | Shininess factor [0..1000]   |                                        |
| map_Kd        | Texture       | Texture Diffuse              |                                        |
| map_Ka        | Texture       | Texture Ambient              |                                        |
| map_Ks        | Texture       | Texture Specular             |                                        |
| map_Ns        | Texture       | Texture Glossiness           |                                        |
| map_Pr        | Texture       | Texture Roughness            |                                        |
| map_Pm        | Texture       | Texture Metalness            |                                        |
| map_Ps        | Texture       | Texture Sheen                |                                        |
| map_d         | Texture       | Opacity Texture (alpha)      |                                        |
| map_bump      | Texture       | Normal texture               |                                        |
| map_Po        | Texture       | Texture Occlusion            |                                        |
| sharpness     | double        | Sharpness value [0..1000]    |                                        |
| d             | Opacity       | Dissolve factor              |                                        |
| disp          | Texture       | Displacement map             |                                        |
| decal         | Texture       | Stencil decal                |                                        |
| bump          | Texture       | Normal texture               |                                        |
| illum         | int           | Illumination [0..10]         |                                        |
| Ni            | double        | Optical density              |                                        |
| Tr            | double        | Transparency                 |                                        |
| refl          | Reflection    | Reflection map               |                                        |
| Ke            | Color         | Color Emissive               | Physically Rendering/Clara.io          |
| Pr            | double        | Roughness factor             | Physically Rendering/Clara.io          |
| Pm            | double        | Metalness factor             | Physically Rendering/Clara.io          |
| Ps            | double        | Sheen factor                 | Physically Rendering/Clara.io          |
| Pc            | double        | Thickness factor             | Physically Rendering/Clara.io          |
| Pcr           | double        | Roughness factor             | Physically Rendering/Clara.io          |
| aniso         | double        | Anisotropy                   | Physically Rendering/Clara.io          |
| anisor        | double        | Anisotropy rotation          | Physically Rendering/Clara.io          |
| map_Ke        | Texture       | Texture Emissive             | Physically Rendering/Clara.io          |
| norm          | Texture       | Texture Normal               | Physically Rendering/Clara.io          |
| map_RMA       | Texture       | Texture RMA                  | DirectXMesh/Microsoft's DirectX engine |
| map_ORM       | Texture       | Texture ORM                  | DirectXMesh/Microsoft's DirectX engine |


## example.mtl

```
# Example of a material file that will be used in the subsequent examples

newmtl mat_1
Ka 0.328013 0.328013 0.328013
Kd 0.627451 0.627451 0.627451
Ns 750.000000

newmtl mat_2
Ka 0.031400 0.031400 0.031400
Kd 0.098039 0.098039 0.098039
Ks 0.977692 0.968577 0.945277
```
Let's consider a scenario where our 3D graphics application is required to extract the values of Kd, Ka, and Ks for all materials from the material file. In the event that these values are not present in the file, we will implement our own default values, such as blue as the default color.
In this system, there are three possible approaches to achieve this, as demonstrated below.

## Method 1

Classic way to check values. Load the file, iterate over all the materials, and retrieve the desired values. Utilize the hasValue() function to check if the value has been read, which returns true if the value exists. 

```cpp
#include "WavefrontMTL.h"
#include <iostream>

int main()
{
	mtl::Load file;

	if( !file.load("C:\\example.mtl") )
		return 1;

	mtl::Color K;

	K.color = mtl::rgb(0, 0, 1); //Blue

	//Loop over all materials and check Ka, Kd and Ks

	for( auto& material : file.materials() )
	{
		if( !material.Ka.hasValue() )
			material.Ka = K; //Set default

		if( !material.Kd.hasValue() )
			material.Kd = K; //Set default

		if( !material.Ks.hasValue() )
			material.Ks = K; //Set default
	}

	//Trace out data
	for (auto& material : file.materials())
	{
		std::string name = material.name;

		std::cout << "newmtl " << name << std::endl;

		std::cout << "Ka " << " " << material.Ka.color.r << " " << material.Ka.color.g << " " << material.Ka.color.b << std::endl;
		std::cout << "Kd " << " " << material.Kd.color.r << " " << material.Kd.color.g << " " << material.Kd.color.b << std::endl;
		std::cout << "Ks " << " " << material.Ks.color.r << " " << material.Ks.color.g << " " << material.Ks.color.b << std::endl;

		std::cout << std::endl;
	}

	return 0;
}
```
Bye running this code we get
```
newmtl mat_1
Ka  0.328013 0.328013 0.328013
Kd  0.627451 0.627451 0.627451
Ks  0 0 1

newmtl mat_2
Ka  0.0314 0.0314 0.0314
Kd  0.098039 0.098039 0.098039
Ks  0.977692 0.968577 0.945277
```

## Method 2

This approach is the preferred method, as it allows for pre-defined default values to be used if a value is not found.

```cpp
#include "WavefrontMTL.h"
#include <iostream>

int main()
{
	mtl::Material defaultValues;

	defaultValues.Ka.color = mtl::rgb(0, 0, 1);
	defaultValues.Kd.color = mtl::rgb(0, 0, 1);
	defaultValues.Ks.color = mtl::rgb(0, 0, 1);

	mtl::Load file(defaultValues);

	if( !file.load("C:\\example.mtl") )
		return 1;

	for( auto& material : file.materials() )
	{
		std::string name = material.name;

		std::cout << "newmtl " << name << std::endl;

		std::cout << "Ka " << " " << material.Ka.color.r << " " << material.Ka.color.g << " " << material.Ka.color.b << std::endl;
		std::cout << "Kd " << " " << material.Kd.color.r << " " << material.Kd.color.g << " " << material.Kd.color.b << std::endl;
		std::cout << "Ks " << " " << material.Ks.color.r << " " << material.Ks.color.g << " " << material.Ks.color.b << std::endl;

		std::cout << std::endl;
	}

	return 0;
}
```
Bye running this code we get the same result as Method 1. The value for Ks is not defined for material_1 in the file, and as per the default settings, Ks has been assigned the value "blue".

```
newmtl mat_1
Ka  0.328013 0.328013 0.328013
Kd  0.627451 0.627451 0.627451
Ks  0 0 1

newmtl mat_2
Ka  0.0314 0.0314 0.0314
Kd  0.098039 0.098039 0.098039
Ks  0.977692 0.968577 0.945277
```

## Method 3

This approach utilizes a material file as a source for default values, which can be defined as desired. The material file follows the same rules and format as a standard MTL file. Let's create a basic file for demonstration. 

```
# My default values
newmtl blue
Ka 0 0 1
Kd 0 0 1
Ks 0 0 1 
newmtl red
Ka 1 0 0
Kd 1 0 0
Ks 1 0 0 
```

```cpp
#include "WavefrontMTL.h"
#include <iostream>

int main()
{
	mtl::Load defaultFile;

	if( !defaultFile.load("C:\\default.mtl") )
		return 1;

	mtl::Material defaultValues;

	if( !defaultFile.lookup("blue", defaultValues) )
		return 1;

	mtl::Load file(defaultValues);

	if( !file.load("C:\\example.mtl") )
		return 1;

	for( auto& material : file.materials() )
	{
		std::string name = material.name;

		std::cout << "newmtl " << name << std::endl;

		std::cout << "Ka " << " " << material.Ka.color.r << " " << material.Ka.color.g << " " << material.Ka.color.b << std::endl;
		std::cout << "Kd " << " " << material.Kd.color.r << " " << material.Kd.color.g << " " << material.Kd.color.b << std::endl;
		std::cout << "Ks " << " " << material.Ks.color.r << " " << material.Ks.color.g << " " << material.Ks.color.b << std::endl;

		std::cout << std::endl;
	}

	return 0;
}
```

Bye running this code we get the same result. 

```
newmtl mat_1
Ka  0.328013 0.328013 0.328013
Kd  0.627451 0.627451 0.627451
Ks  0 0 1

newmtl mat_2
Ka  0.0314 0.0314 0.0314
Kd  0.098039 0.098039 0.098039
Ks  0.977692 0.968577 0.945277
```

One of the advantages of this approach is that there is no need for additional programming. If you wish to modify default values, you can simply update the default.mtl file.

## License
WavefrontMTL is licensed under MIT license.

