template <class MeshClass>
class IteratorT
{
public:

	typedef TargetType& TargetRef;
	typedef TargetType* TargetPtr;
	typedef index_type  IterBase;

//	IteratorT() : _current(-1), _mesh(NULL) {}

	IteratorT(MeshClass* mesh) : _current(INVALID_INDEX), _mesh(mesh)
	{
		if (_mesh) _current = 0;		
	}

	IteratorT(MeshClass* mesh, size_type start_pos) : _current(INVALID_INDEX), _mesh(mesh)
	{
		if (_mesh && (TOTAL>0))
		{
			_current = start_pos;
		}
	}

	IteratorT(const IteratorT& iter) :
	_current(iter._current), _mesh(iter._mesh)
	{}

	IteratorT& operator=(const IteratorT& rhs)
	{
		_current = rhs._current;
		_mesh  = rhs._mesh;
		return *this;
	}

	bool operator==(const IteratorT& rhs) {
		return ((_current==rhs._current) && (_mesh==rhs._mesh));
	}

	bool operator!=(const IteratorT& rhs) {
		return !operator==(rhs);
	}

	IteratorT& operator++() {
		++_current;
		return *this;
	}

	IteratorT& operator--() {
		--_current;
		return *this;
	}

	TargetRef operator*() const { return *TARGETPTR; }

	TargetPtr operator->() const { return TARGETPTR; }

	operator TargetPtr() const { return TARGETPTR; }

	operator TargetHandle() const { return HANDLE; }

	TargetHandle Handle() const { return HANDLE; }

	inline bool NotEnd() const { return (_current<TOTAL); }

	operator bool() const {	return this->NotEnd(); }

private:
	IterBase _current;
	MeshClass *_mesh;
};
