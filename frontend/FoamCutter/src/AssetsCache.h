#pragma once
#include "Singleton.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/ImageIo.h"

class AssetCache
{

public:
	AssetCache(){};



	void pushTextTexture(std::string key, ci::gl::TextureRef texture){
		textTextures.push_back(std::make_pair(key, texture));

	}






	ci::gl::TextureRef getTextTexture(std::string key)
	{
		for (auto p : textTextures)
		{
			if (p.first == key)
			{
				return p.second;
			}
		}


		return nullptr;

	}
	std::vector<std::pair<std::string, ci::gl::TextureRef  >> textTextures;



	// caching textures
	ci::gl::TextureRef getTexture(std::string assetPath)
	{
		for (auto p : textures)
		{
			if (p.first == assetPath)
			{
				return p.second;
			}
		}

		ci::gl::TextureRef texture = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset(assetPath)));
		textures.push_back(std::make_pair(assetPath, texture));

		return texture;
	
	}
	std::vector<std::pair<std::string, ci::gl::TextureRef  >> textures;
	
    
    // caching fonts.
	ci::Font getFont(std::string name,int size)
	{
		std::string fontName = name + std::to_string(size);
		
		for (auto p : fonts)
		{
			if (p.first == fontName)
			{
				
				return p.second;
			}
		}

		ci::Font font = ci::Font(ci::app::loadAsset(name), size);
		fonts.push_back(std::make_pair(fontName, font));
		return font;

	}
	std::vector<std::pair<std::string, ci::Font  >> fonts;
    
    
    // caching shaders.
    ci::gl::GlslProgRef getProgram(std::string programName)
    {
        for (auto p : programs)
        {
            if (p.first == programName)
            {
                return p.second;
            }
        }
        
        
        try{
            ci::gl::GlslProgRef program = ci::gl::GlslProg::create( ci::gl::GlslProg::Format().vertex( ci::app::loadAsset("shaders/" + programName + ".vert" ) )
                                                                .fragment( ci::app::loadAsset( "shaders/" + programName + ".frag" ) ));
            programs.push_back(std::make_pair(programName, program));
            return program;

            
        }
        catch( ci::gl::GlslProgCompileExc ex ) {
           ci::app::console() << ex.what() << std::endl;
            //exit(0);
        }
        
        return nullptr;
        
    }
    std::vector<std::pair<std::string, ci::gl::GlslProgRef  >> programs;
    
    

};



typedef Singleton< AssetCache>  AssetCacheSingleton;

inline  AssetCache* CACHE() {
	return  AssetCacheSingleton::Instance();
}
