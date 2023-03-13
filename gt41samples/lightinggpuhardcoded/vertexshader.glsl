#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec4 Colour;

out vec4 Colour0;

// Transforms
uniform mat4 gModelToWorldTransform;
uniform mat4 gWorldToViewTransform;
uniform mat4 gProjectionTransform;

                                                                   
void main()
{  
	// Transform the vertex from local space to homogeneous clip space 
	vec4 vertexPositionInModelSpace = vec4(Position, 1);
	vec4 vertexInWorldSpace = gModelToWorldTransform * vertexPositionInModelSpace;
	vec4 vertexInCameraSpace = gWorldToViewTransform * vertexInWorldSpace;
	vec4 vertexInClipSpace = gProjectionTransform * vertexInCameraSpace;
	gl_Position = vertexInClipSpace;

	// Hardcored lighting variables
	// Ambient light parameters
    vec3 ambientLightIntensity = vec3(0.5f, 0.5f, 0.5f);
	// Directional light parameters
	vec3 directionalLightIntensity = vec3(1.0f, 1.0f, 1.0f);
	vec3 directionalLightDirection = vec3(0.0f, 0.0f, -1.0f);
	// Material constants
	float ka = 0.2f;
	float kd = 0.5f;

	// Calculate the ambient light intensity at the vertex
	// Ia = Ka * ambientLightIntensity
	vec4 ambientIntensity = ka * vec4(ambientLightIntensity, 1.0);

	// Calculate the directional light intensity at the vertex
	// Find the normal in world space and normalise it
	vec3 normalInWorldSpace = (gModelToWorldTransform * vec4(Normal, 0.0)).xyz;
	normalInWorldSpace = normalize(normalInWorldSpace);
	// Setup the light direction and normalise it
	vec3 lightDirection = normalize(-directionalLightDirection);


	//lightDirection = normalize(gDirectionalLightDirection);
	// Id = kd * lightItensity * N.L
	// Calculate N.L
	float diffuseFactor = dot(normalInWorldSpace, lightDirection);
	diffuseFactor = clamp(diffuseFactor, 0.0, 1.0);
	// N.L * light source colour * intensity
    vec4 diffuseIntensity = kd * vec4(directionalLightIntensity, 1.0f) * diffuseFactor;
   
	// Final vertex colour is the product of the vertex colour
	// and the total light intensity at the vertex 

	Colour0 = Colour * (ambientIntensity + diffuseIntensity);
}