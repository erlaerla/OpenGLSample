#ifndef __OPENGLSAMPLE_FRAMEWORK_H__
#define __OPENGLSAMPLE_FRAMEWORK_H__

class Framework
{
public:
	Framework();
	virtual ~Framework();

	static Framework* GetSingletonPtr();

	int		Startup();
	void	Shutdown();
	void	Loop();

	virtual void	OnKeyProc(int key, int action){}

protected:
	virtual int		Initialize() = 0;
	virtual void	Uninitialize() = 0;
	virtual void	Render() = 0;
};

#endif