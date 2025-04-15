#pragma once
#include <string>

struct Message {
	std::string text;

	std::string serialize() const {
		return text;
	}

	static Message deserialize(const std::string& raw) {
		return Message{ raw };
	}
};