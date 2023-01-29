#include <myengine/myengine.h>

using namespace myengine;

struct Player : Component
{
	void onTick(float deltaTs);

	void onInit();

	float getAngle();

private:
	std::shared_ptr<Input> m_input;

	std::shared_ptr<Transform> m_transform;

	float m_angle;
};

struct CamController : Component
{

	void onTick(float deltaTs);

	void onInit();

	void setPlayer(std::shared_ptr<Player> _player);

private:
	bool m_rCam;

	bool m_camTog;

	std::shared_ptr<Input> m_input;

	std::shared_ptr<Player> m_player;

	rend::vec3 m_posOffset;

	float m_xAng;
};

struct Milk : Component
{
	void onInit();

	void onTick(float deltaTs);

	void randomisePos();

	void setData(std::shared_ptr<Entity> _player, std::shared_ptr<BoxCollider> _collider);

	int getScore();

private:
	std::shared_ptr<Entity> m_player;

	std::shared_ptr<BoxCollider> m_collider;

	int m_hitCount;
};

struct Obstacle : Component
{
	void onTick(float deltaTs);

	void randomisePos();

	void setData(std::shared_ptr<Entity> _player, std::shared_ptr<BoxCollider> _collider);

private:
	std::shared_ptr<Entity> m_player;

	std::shared_ptr<BoxCollider> m_collider;
};

struct Song : Component
{
	void onInit();

	void onTick(float deltaTs);

	void play();

	void setCheck(bool _check);

	void setData(std::shared_ptr<SoundSource> _song, std::shared_ptr<Transform> _playerTransform);

private:
	bool m_check;

	std::shared_ptr<SoundSource> m_song;

	std::shared_ptr<Transform> m_playerTransform;
};

struct Announcement : Component
{
	void onInit();

	void onTick(float deltaTs);

	void setData(std::shared_ptr<SoundSource> _self, std::shared_ptr<Song> _song, std::shared_ptr<Transform> _player);

private:
	std::shared_ptr<SoundSource> m_self;

	std::shared_ptr<Song> m_song;

	std::shared_ptr<Transform> m_playerTransform;

	bool m_doPlay;
};