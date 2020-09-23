#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_list.clear();
	this->frame_list.clear();

	for (int x = -180; x <= 180; x += 360) {

		for (int y = -180; y <= 180; y += 360) {

			float noise_seed_1 = ofRandom(1000);
			float noise_seed_2 = ofRandom(1000);

			for (int i = 0; i < 150; i++) {

				int param_start = ofMap(ofNoise(noise_seed_1, ofGetFrameNum() * 0.003 + i * 0.001), 0, 1, 0, 200);
				int param_end = param_start + ofMap(ofNoise(noise_seed_2, ofGetFrameNum() * 0.003 + i * 0.001), 0, 1, 25, 50);

				ofMesh face, frame;
				frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
				this->setShapeToMesh(face, frame, glm::vec3(x, y, 0), 350, param_start, param_end, ofColor(ofMap(i, 0, 150, 200, 39)), ofColor(ofMap(i, 0, 150, 78, 239)));

				this->face_list.push_back(face);
				this->frame_list.push_back(frame);
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int i = 0; i < this->face_list.size(); i++) {

		this->face_list[i].drawFaces();
		this->frame_list[i].drawWireframe();
	}
}

//--------------------------------------------------------------
void ofApp::setShapeToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float len, int param_start, int param_end, ofColor face_color, ofColor frame_color) {

	vector<glm::vec3> vertices;
	vertices.push_back(location + this->make_point(len, param_start));
	for (int param = param_start; param < param_end; param++) {

		if (param % 25 == 0) { vertices.push_back(location + this->make_point(len, param)); }
	}
	vertices.push_back(location + this->make_point(len, param_end));

	face_target.addVertices(vertices);
	frame_target.addVertices(vertices);

	face_target.addIndex(0); face_target.addIndex(1); face_target.addIndex(2);
	for (int i = 2; i < face_target.getNumVertices() - 1; i++) {

		face_target.addIndex(0); face_target.addIndex(i); face_target.addIndex(i + 1);
	}

	for (int i = 0; i <frame_target.getNumVertices() - 1; i++) {

		frame_target.addIndex(i); frame_target.addIndex(i + 1);
	}

	frame_target.addIndex(0); frame_target.addIndex(face_target.getNumVertices() - 1);	


	for (int i = 0; i < vertices.size(); i++) {

		face_target.addColor(face_color);
		frame_target.addColor(frame_color);
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}