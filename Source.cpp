#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

template <class T>
class MyPipeline
{
private:
	struct Step
	{
		std::string name;
		std::function<T(T)> func;
	};

	std::vector<Step> steps;

public:

	size_t size() const
	{
		return steps.size();
	}

	bool empty() const
	{
		return steps.empty();
	}

	void clear()
	{
		steps.clear();
	}

	template <class F>
	void addStep(const std::string& name, F func)
	{

	}

	void removeStep(size_t index)
	{

	}

	T run(T value) const
	{

	}

	std::vector<T> trace(T value) const
	{

	}

	friend std::ostream& operator<<(std::ostream& stream, const MyPipeline& pipeline)
	{
		stream << "steps count: " << pipeline.size() << std::endl;
		for (size_t i = 0; i < pipeline.steps.size(); i++)
		{
			stream << i << ") " << pipeline.steps[i].name << std::endl;
		}
		return stream;
	}
};

int main()
{

}