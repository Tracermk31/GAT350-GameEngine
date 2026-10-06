#pragma once

#include "pch.h"

#include <map>
#include <string>
#include <fmod.hpp>

namespace ChiefEngine {
	class Audio {
	private:
		FMOD::System* m_audio = nullptr;
		FMOD::ChannelGroup* m_channelGroup_1 = nullptr;
		FMOD::Channel* m_channel_1 = nullptr;
		FMOD::Channel* m_channel_2 = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;

		bool CheckFMODResult(FMOD_RESULT result);
	public:
		bool Initialize();
		void Shutdown();
		void Update();

		/// <summary>
		/// Returns an FMOD Channel based on the provided number
		/// </summary>
		/// <param name="channelNumber">The desired channel number</param>
		/// <returns>An FMOD Channel with the given number, else nullptr</returns>
		inline FMOD::Channel* GetChannel(unsigned short channelNumber) {
			switch (channelNumber) {
			case 1:
				return m_channel_1;
			case 2:
				return m_channel_2;
			}
			return nullptr;
		}

		bool AddSound(const std::string& name, const std::string filepath);

		/// <summary>
		/// Clears the vector of sounds, ensuring they're properly deleted.
		/// </summary>
		inline void ClearSounds() {
			m_sounds.clear();
		}

		bool setSoundLoop(const std::string& name, bool willLoop);

		bool PlaySound(std::string name);
		bool PlaySound(std::string name, FMOD::Channel* channelToPlayOn);
	};
}