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
		if (name.empty())
		{
			throw std::invalid_argument("Error:Empty step name");
		}
		steps.push_back({ name, func });
	}

	void removeStep(size_t index)
	{
		if (index >= steps.size())
		{
			throw std::out_of_range("Index out of range");
		}
		steps.erase(steps.begin() + index);
	}

	T run(T value) const
	{
		T result = value;
		for (size_t i = 0; i < steps.size(); i++)
		{
			result = steps[i].func(result);
		}
		return result;
	}

	std::vector<T> trace(T value) const
	{
		std::vector<T> result;
		T current = value;
		for (size_t i = 0; i < steps.size(); i++)
		{
			current = steps[i].func(current);
			result.push_back(current);
		}
		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, const MyPipeline& pipeline)
	{
		stream << "Steps: " << pipeline.size() << std::endl;
		for (size_t i = 0; i < pipeline.steps.size(); i++)
		{
			stream << i << ") " << pipeline.steps[i].name << std::endl;
		}
		return stream;
	}
};

int main()
{
	MyPipeline<int> intPipe;
	intPipe.addStep("add 5", [](int val) { return val + 5; });
	intPipe.addStep("multiply 2", [](int val) { return val * 2; });
	intPipe.addStep("square", [](int val) { return val*val; });

	std::cout << intPipe << std::endl;

	std::cout << intPipe.run(10) << std::endl;

	auto traceRes = intPipe.trace(10);
	for (const auto& elem : traceRes)
	{
		std::cout << elem << std::endl;
	}
	std::cout << std::endl;

}