#include <stdio.h> 
//�f�t�H���g�̒��ۃV�[���N���X | |/���[�U�[�͂�����p�����ăV�[������������Ɗy 
class AbstractScene {
public:
	// �f�X�g���N�^�[
	virtual ~AbstractScene() {};
	//�`��ȊO�̍X�V����������
	virtual AbstractScene* Update() = 0;
	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const = 0;
};
	// �V�[���}�l�[�W���[�N���X
	// �e�V�[���̐؂�ւ����Ǘ�����B
class SceneManager : public AbstractScene {
private:
	AbstractScene* mScene; // ���݂̃V�[�� 
public:
	// �R���X�g���N�^ 
	SceneManager(AbstractScene* scene) : mScene(scene) { }
	// �f�X�g���N�^ 
	~SceneManager() {
		delete mScene;
	}
	//�`��ȊO�̍X�V����������
	AbstractScene* Update() override;
	//�`��Ɋւ��邱�Ƃ���������
	void Draw() const override;
};
AbstractScene* SceneManager::Update() {
	AbstractScene* p = mScene->Update();
	if (p != mScene) {
		delete mScene;
		mScene = p;
	}
	return p;
}
void SceneManager::Draw() const {
	mScene->Draw();
}

class Title : public AbstractScene {
public:
	// �f�X�g���N�^
	virtual ~Title() {};

	//�`��ȊO�̍X�V����������
	virtual AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;
};
						
class GameMain : public AbstractScene {
public:
	// �f�X�g���N�^ 
	virtual ~GameMain() {};

	//�`��ȊO�̍X�V����������
	virtual AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;
};
						
AbstractScene* Title::Update() {
	int nint;
	scanf_s("%d", &nint);
	if (nint == 1) {
		return new GameMain();
	}
	return this;
}
							
void Title::Draw() const {
	printf("Title�ł��B\n");
	printf("�����l����͂��Ă�������>");
}
									
AbstractScene* GameMain::Update() {
	int nint;
	scanf_s("%d", &nint); if (nint == 1) {
		return nullptr;
	}
	return this;
}
										
void GameMain::Draw() const {
	printf("GameMain�ł��B\n");
	printf("�����l����͂��Ă�������>");
}
												
int main() {
	SceneManager sceneMng(new Title());

	printf("�����l����͂��Ă�������>");
	while (sceneMng.Update() != nullptr) {
		sceneMng.Draw();
	}

	printf("�������I�����܂��B\n");
	return 0;
}
