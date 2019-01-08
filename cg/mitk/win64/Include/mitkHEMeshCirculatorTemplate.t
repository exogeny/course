template <class MeshClass>
class CirculatorT
{
public:
	typedef TargetType&   TargetRef;
	typedef TargetType*   TargetPtr;

//	CirculatorT() : _start(NULL), _current(NULL), _mesh(NULL) _active(false) {}

	CirculatorT(MeshClass *mesh, SourceHandle roundCenter)
	{
		_mesh = mesh;
		_active = false;
		if (roundCenter.IsValid() && _mesh!=NULL) { _current = _start = START; POSTINIT; }
		else { _current = _start = INVALID_INDEX; }		
	}

	CirculatorT(MeshClass *mesh, HalfEdgeHandle start)
	{
		_mesh = mesh;
		_active = false;
		if (_mesh) { _current = _start = start; POSTINIT; }
		else { _current = _start = INVALID_INDEX; }
	}

	CirculatorT(const CirculatorT& iter) :
	_start(iter._start), _current(iter._current), _mesh(iter._mesh), _active(iter._active)
	{ POSTINIT; }

	CirculatorT& operator=(const CirculatorT& rhs)
	{
		_start   = rhs._start;
		_current = rhs._current;
		_mesh    = rhs._mesh;
		_active  = rhs._active;
		return *this;
	}

	bool operator==(const CirculatorT& rhs) {
		return ((_start==rhs._start) && 
			(_current==rhs._current) && 
			(_mesh==rhs._mesh) &&
			(_active==rhs._active));
	}

	bool operator!=(const CirculatorT& rhs) {
		return !operator==(rhs);
	}

	CirculatorT& operator++() {
		_active = true;
		NEXT;
		return *this;
	}

	CirculatorT& operator--() {
		_active = true;
		PREV;
		return *this;
	}

	TargetRef operator*() const { return TARGET; }

	TargetPtr operator->() const { return &TARGET; }

	operator TargetHandle() const { return HANDLE; }

	TargetHandle Handle() const { return HANDLE; }

	inline bool NotEnd() const { 
		return (((_start!=_current) || (!_active)) && (_current.IsValid())); 
	}

	operator bool() const {	return this->NotEnd(); }

private:
	HalfEdgeHandle _start, _current;
	MeshClass *_mesh;
	bool _active;
};
