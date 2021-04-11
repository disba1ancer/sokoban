/*
 * shaderProgram.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: disba1ancer
 */

#include "shaderProgram.h"

namespace sokoban {

const char vertShader[] = R"shader(
#version 140

in vec2 vertex;
out vec2 uv;
flat out int texInd;

void main() {
  const mat4x2 UVs = mat4x2(0, 0, 0, 1, 1, 1, 1, 0);
  uv = UVs[int(mod(gl_VertexID, 4))];
  gl_Position = vec4(vertex, 0, 1);
  texInd = gl_VertexID / 4;
  texInd = 1 - texInd;
  texInd = max(0, min(texInd, 1));
}
)shader";

const char fragShader[] = R"shader(
#version 140

uniform usampler2D level;
uniform sampler2DArray textureArray;
uniform bool levelMode;

in vec2 uv;
flat in int texInd;
out vec4 outColor;

vec4 tiledTexture(in usampler2D tileMap, in sampler2DArray textures, in vec2 uv);

void main() {
  //outColor = vec4(float(texture(level, uv).x) / 2);
  if (levelMode) {
    outColor = tiledTexture(level, textureArray, uv);
  } else {
    outColor = texture(textureArray, vec3(uv, 2 + texInd));
  }
  if (outColor.a < .5) discard;
  //outColor = vec4(1, 1, 1, 1);
}

vec4 tiledTexture(in usampler2D tileMap, in sampler2DArray textures, in vec2 uv) {
	vec2 tileMapSize = textureSize(tileMap, 0);
	int index = int(texture(tileMap, uv).r) - 1;
	if (index < 0) return vec4(-1);
	vec2 inTileCoord = fract(uv * tileMapSize);
	//vec2 tileSize = textureSize(atlas, 0) / atlasTilesCount;
	//vec2 srcTilePos = vec2(mod(index, atlasTilesCount.x), -(1 + floor(index / atlasTilesCount.x)));
	vec3 srcTileCoord = vec3(inTileCoord, float(index));
	return texture(textures, srcTileCoord).rgba;
}

)shader";

} /* namespace sokoban */
