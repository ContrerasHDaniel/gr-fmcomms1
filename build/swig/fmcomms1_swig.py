# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_fmcomms1_swig', [dirname(__file__)])
        except ImportError:
            import _fmcomms1_swig
            return _fmcomms1_swig
        if fp is not None:
            try:
                _mod = imp.load_module('_fmcomms1_swig', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _fmcomms1_swig = swig_import_helper()
    del swig_import_helper
else:
    import _fmcomms1_swig
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


def _swig_setattr_nondynamic_method(set):
    def set_attr(self,name,value):
        if (name == "thisown"): return self.this.own(value)
        if hasattr(self,name) or (name == "this"):
            set(self,name,value)
        else:
            raise AttributeError("You cannot add attributes to %s" % self)
    return set_attr



def high_res_timer_now():
  """high_res_timer_now() -> gr::high_res_timer_type"""
  return _fmcomms1_swig.high_res_timer_now()

def high_res_timer_now_perfmon():
  """high_res_timer_now_perfmon() -> gr::high_res_timer_type"""
  return _fmcomms1_swig.high_res_timer_now_perfmon()

def high_res_timer_tps():
  """high_res_timer_tps() -> gr::high_res_timer_type"""
  return _fmcomms1_swig.high_res_timer_tps()

def high_res_timer_epoch():
  """high_res_timer_epoch() -> gr::high_res_timer_type"""
  return _fmcomms1_swig.high_res_timer_epoch()
DEFAULT_BUFFER_SIZE = _fmcomms1_swig.DEFAULT_BUFFER_SIZE
class fmcomms1_source(object):
    """
    <+description of block+>

    Constructor Specific Documentation:

    Return a shared_ptr to a new instance of fmcomms1::fmcomms1_source.

    To avoid accidental use of raw pointers, fmcomms1::fmcomms1_source's constructor is in a private implementation class. fmcomms1::fmcomms1_source::make is the public interface for creating new instances.

    Args:
        uri : 
        frequency : 
        samplerate : 
        bandwidth : 
        device : 
        device_phy : 
        channels : 
        buffer_size : 
        decimation : 
    """
    thisown = _swig_property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    def make(*args, **kwargs):
        """
        make(std::string const & uri, unsigned long frequency, unsigned long samplerate, unsigned long bandwidth, 
            std::string const & device, std::string const & device_phy, 
            std::vector< std::string,std::allocator< std::string > > const & channels, 
            unsigned int buffer_size=0x8000, unsigned int decimation=0) -> fmcomms1_source_sptr

        <+description of block+>

        Constructor Specific Documentation:

        Return a shared_ptr to a new instance of fmcomms1::fmcomms1_source.

        To avoid accidental use of raw pointers, fmcomms1::fmcomms1_source's constructor is in a private implementation class. fmcomms1::fmcomms1_source::make is the public interface for creating new instances.

        Args:
            uri : 
            frequency : 
            samplerate : 
            bandwidth : 
            device : 
            device_phy : 
            channels : 
            buffer_size : 
            decimation : 
        """
        return _fmcomms1_swig.fmcomms1_source_make(*args, **kwargs)

    make = staticmethod(make)
    def make_from(*args, **kwargs):
        """
        make_from(iio_context * ctx, unsigned long frequency, unsigned long samplerate, unsigned long bandwidth, 
            std::string const & device, std::string const & device_phy, std::vector< std::string,std::allocator< std::string > > const & channels, 
            unsigned int buffer_size=0x8000, 
            unsigned int decimation=0) -> fmcomms1_source_sptr
        """
        return _fmcomms1_swig.fmcomms1_source_make_from(*args, **kwargs)

    make_from = staticmethod(make_from)
    def set_buffer_size(self, *args, **kwargs):
        """set_buffer_size(fmcomms1_source self, unsigned int buffer_size)"""
        return _fmcomms1_swig.fmcomms1_source_set_buffer_size(self, *args, **kwargs)

    __swig_destroy__ = _fmcomms1_swig.delete_fmcomms1_source
    __del__ = lambda self : None;
fmcomms1_source_swigregister = _fmcomms1_swig.fmcomms1_source_swigregister
fmcomms1_source_swigregister(fmcomms1_source)

def fmcomms1_source_make(*args, **kwargs):
  """
    fmcomms1_source_make(std::string const & uri, unsigned long frequency, unsigned long samplerate, unsigned long bandwidth, 
        std::string const & device, std::string const & device_phy, 
        std::vector< std::string,std::allocator< std::string > > const & channels, 
        unsigned int buffer_size=0x8000, unsigned int decimation=0) -> fmcomms1_source_sptr

    <+description of block+>

    Constructor Specific Documentation:

    Return a shared_ptr to a new instance of fmcomms1::fmcomms1_source.

    To avoid accidental use of raw pointers, fmcomms1::fmcomms1_source's constructor is in a private implementation class. fmcomms1::fmcomms1_source::make is the public interface for creating new instances.

    Args:
        uri : 
        frequency : 
        samplerate : 
        bandwidth : 
        device : 
        device_phy : 
        channels : 
        buffer_size : 
        decimation : 
    """
  return _fmcomms1_swig.fmcomms1_source_make(*args, **kwargs)

def fmcomms1_source_make_from(*args, **kwargs):
  """
    fmcomms1_source_make_from(iio_context * ctx, unsigned long frequency, unsigned long samplerate, unsigned long bandwidth, 
        std::string const & device, std::string const & device_phy, std::vector< std::string,std::allocator< std::string > > const & channels, 
        unsigned int buffer_size=0x8000, 
        unsigned int decimation=0) -> fmcomms1_source_sptr
    """
  return _fmcomms1_swig.fmcomms1_source_make_from(*args, **kwargs)

class fmcomms1_source_sptr(object):
    """Proxy of C++ boost::shared_ptr<(gr::fmcomms1::fmcomms1_source)> class"""
    thisown = _swig_property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """
        __init__(boost::shared_ptr<(gr::fmcomms1::fmcomms1_source)> self) -> fmcomms1_source_sptr
        __init__(boost::shared_ptr<(gr::fmcomms1::fmcomms1_source)> self, fmcomms1_source p) -> fmcomms1_source_sptr
        """
        this = _fmcomms1_swig.new_fmcomms1_source_sptr(*args)
        try: self.this.append(this)
        except: self.this = this
    def __deref__(self):
        """__deref__(fmcomms1_source_sptr self) -> fmcomms1_source"""
        return _fmcomms1_swig.fmcomms1_source_sptr___deref__(self)

    __swig_destroy__ = _fmcomms1_swig.delete_fmcomms1_source_sptr
    __del__ = lambda self : None;
    def make(self, *args, **kwargs):
        """
        make(fmcomms1_source_sptr self, std::string const & uri, unsigned long frequency, unsigned long samplerate, unsigned long bandwidth, 
            std::string const & device, std::string const & device_phy, 
            std::vector< std::string,std::allocator< std::string > > const & channels, 
            unsigned int buffer_size=0x8000, unsigned int decimation=0) -> fmcomms1_source_sptr

        <+description of block+>

        Constructor Specific Documentation:

        Return a shared_ptr to a new instance of fmcomms1::fmcomms1_source.

        To avoid accidental use of raw pointers, fmcomms1::fmcomms1_source's constructor is in a private implementation class. fmcomms1::fmcomms1_source::make is the public interface for creating new instances.

        Args:
            uri : 
            frequency : 
            samplerate : 
            bandwidth : 
            device : 
            device_phy : 
            channels : 
            buffer_size : 
            decimation : 
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_make(self, *args, **kwargs)

    def make_from(self, *args, **kwargs):
        """
        make_from(fmcomms1_source_sptr self, iio_context * ctx, unsigned long frequency, unsigned long samplerate, unsigned long bandwidth, 
            std::string const & device, std::string const & device_phy, std::vector< std::string,std::allocator< std::string > > const & channels, 
            unsigned int buffer_size=0x8000, 
            unsigned int decimation=0) -> fmcomms1_source_sptr
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_make_from(self, *args, **kwargs)

    def set_buffer_size(self, *args, **kwargs):
        """set_buffer_size(fmcomms1_source_sptr self, unsigned int buffer_size)"""
        return _fmcomms1_swig.fmcomms1_source_sptr_set_buffer_size(self, *args, **kwargs)

    def history(self):
        """history(fmcomms1_source_sptr self) -> unsigned int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_history(self)

    def declare_sample_delay(self, *args):
        """
        declare_sample_delay(fmcomms1_source_sptr self, int which, int delay)
        declare_sample_delay(fmcomms1_source_sptr self, unsigned int delay)
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_declare_sample_delay(self, *args)

    def sample_delay(self, *args, **kwargs):
        """sample_delay(fmcomms1_source_sptr self, int which) -> unsigned int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_sample_delay(self, *args, **kwargs)

    def output_multiple(self):
        """output_multiple(fmcomms1_source_sptr self) -> int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_output_multiple(self)

    def relative_rate(self):
        """relative_rate(fmcomms1_source_sptr self) -> double"""
        return _fmcomms1_swig.fmcomms1_source_sptr_relative_rate(self)

    def start(self):
        """start(fmcomms1_source_sptr self) -> bool"""
        return _fmcomms1_swig.fmcomms1_source_sptr_start(self)

    def stop(self):
        """stop(fmcomms1_source_sptr self) -> bool"""
        return _fmcomms1_swig.fmcomms1_source_sptr_stop(self)

    def nitems_read(self, *args, **kwargs):
        """nitems_read(fmcomms1_source_sptr self, unsigned int which_input) -> uint64_t"""
        return _fmcomms1_swig.fmcomms1_source_sptr_nitems_read(self, *args, **kwargs)

    def nitems_written(self, *args, **kwargs):
        """nitems_written(fmcomms1_source_sptr self, unsigned int which_output) -> uint64_t"""
        return _fmcomms1_swig.fmcomms1_source_sptr_nitems_written(self, *args, **kwargs)

    def max_noutput_items(self):
        """max_noutput_items(fmcomms1_source_sptr self) -> int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_max_noutput_items(self)

    def set_max_noutput_items(self, *args, **kwargs):
        """set_max_noutput_items(fmcomms1_source_sptr self, int m)"""
        return _fmcomms1_swig.fmcomms1_source_sptr_set_max_noutput_items(self, *args, **kwargs)

    def unset_max_noutput_items(self):
        """unset_max_noutput_items(fmcomms1_source_sptr self)"""
        return _fmcomms1_swig.fmcomms1_source_sptr_unset_max_noutput_items(self)

    def is_set_max_noutput_items(self):
        """is_set_max_noutput_items(fmcomms1_source_sptr self) -> bool"""
        return _fmcomms1_swig.fmcomms1_source_sptr_is_set_max_noutput_items(self)

    def set_min_noutput_items(self, *args, **kwargs):
        """set_min_noutput_items(fmcomms1_source_sptr self, int m)"""
        return _fmcomms1_swig.fmcomms1_source_sptr_set_min_noutput_items(self, *args, **kwargs)

    def min_noutput_items(self):
        """min_noutput_items(fmcomms1_source_sptr self) -> int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_min_noutput_items(self)

    def max_output_buffer(self, *args, **kwargs):
        """max_output_buffer(fmcomms1_source_sptr self, int i) -> long"""
        return _fmcomms1_swig.fmcomms1_source_sptr_max_output_buffer(self, *args, **kwargs)

    def set_max_output_buffer(self, *args):
        """
        set_max_output_buffer(fmcomms1_source_sptr self, long max_output_buffer)
        set_max_output_buffer(fmcomms1_source_sptr self, int port, long max_output_buffer)
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_set_max_output_buffer(self, *args)

    def min_output_buffer(self, *args, **kwargs):
        """min_output_buffer(fmcomms1_source_sptr self, int i) -> long"""
        return _fmcomms1_swig.fmcomms1_source_sptr_min_output_buffer(self, *args, **kwargs)

    def set_min_output_buffer(self, *args):
        """
        set_min_output_buffer(fmcomms1_source_sptr self, long min_output_buffer)
        set_min_output_buffer(fmcomms1_source_sptr self, int port, long min_output_buffer)
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_set_min_output_buffer(self, *args)

    def pc_noutput_items(self):
        """pc_noutput_items(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_noutput_items(self)

    def pc_noutput_items_avg(self):
        """pc_noutput_items_avg(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_noutput_items_avg(self)

    def pc_noutput_items_var(self):
        """pc_noutput_items_var(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_noutput_items_var(self)

    def pc_nproduced(self):
        """pc_nproduced(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_nproduced(self)

    def pc_nproduced_avg(self):
        """pc_nproduced_avg(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_nproduced_avg(self)

    def pc_nproduced_var(self):
        """pc_nproduced_var(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_nproduced_var(self)

    def pc_input_buffers_full(self, *args):
        """
        pc_input_buffers_full(fmcomms1_source_sptr self, int which) -> float
        pc_input_buffers_full(fmcomms1_source_sptr self) -> pmt_vector_float
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_input_buffers_full(self, *args)

    def pc_input_buffers_full_avg(self, *args):
        """
        pc_input_buffers_full_avg(fmcomms1_source_sptr self, int which) -> float
        pc_input_buffers_full_avg(fmcomms1_source_sptr self) -> pmt_vector_float
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_input_buffers_full_avg(self, *args)

    def pc_input_buffers_full_var(self, *args):
        """
        pc_input_buffers_full_var(fmcomms1_source_sptr self, int which) -> float
        pc_input_buffers_full_var(fmcomms1_source_sptr self) -> pmt_vector_float
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_input_buffers_full_var(self, *args)

    def pc_output_buffers_full(self, *args):
        """
        pc_output_buffers_full(fmcomms1_source_sptr self, int which) -> float
        pc_output_buffers_full(fmcomms1_source_sptr self) -> pmt_vector_float
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_output_buffers_full(self, *args)

    def pc_output_buffers_full_avg(self, *args):
        """
        pc_output_buffers_full_avg(fmcomms1_source_sptr self, int which) -> float
        pc_output_buffers_full_avg(fmcomms1_source_sptr self) -> pmt_vector_float
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_output_buffers_full_avg(self, *args)

    def pc_output_buffers_full_var(self, *args):
        """
        pc_output_buffers_full_var(fmcomms1_source_sptr self, int which) -> float
        pc_output_buffers_full_var(fmcomms1_source_sptr self) -> pmt_vector_float
        """
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_output_buffers_full_var(self, *args)

    def pc_work_time(self):
        """pc_work_time(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_work_time(self)

    def pc_work_time_avg(self):
        """pc_work_time_avg(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_work_time_avg(self)

    def pc_work_time_var(self):
        """pc_work_time_var(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_work_time_var(self)

    def pc_work_time_total(self):
        """pc_work_time_total(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_work_time_total(self)

    def pc_throughput_avg(self):
        """pc_throughput_avg(fmcomms1_source_sptr self) -> float"""
        return _fmcomms1_swig.fmcomms1_source_sptr_pc_throughput_avg(self)

    def set_processor_affinity(self, *args, **kwargs):
        """set_processor_affinity(fmcomms1_source_sptr self, std::vector< int,std::allocator< int > > const & mask)"""
        return _fmcomms1_swig.fmcomms1_source_sptr_set_processor_affinity(self, *args, **kwargs)

    def unset_processor_affinity(self):
        """unset_processor_affinity(fmcomms1_source_sptr self)"""
        return _fmcomms1_swig.fmcomms1_source_sptr_unset_processor_affinity(self)

    def processor_affinity(self):
        """processor_affinity(fmcomms1_source_sptr self) -> std::vector< int,std::allocator< int > >"""
        return _fmcomms1_swig.fmcomms1_source_sptr_processor_affinity(self)

    def active_thread_priority(self):
        """active_thread_priority(fmcomms1_source_sptr self) -> int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_active_thread_priority(self)

    def thread_priority(self):
        """thread_priority(fmcomms1_source_sptr self) -> int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_thread_priority(self)

    def set_thread_priority(self, *args, **kwargs):
        """set_thread_priority(fmcomms1_source_sptr self, int priority) -> int"""
        return _fmcomms1_swig.fmcomms1_source_sptr_set_thread_priority(self, *args, **kwargs)

    def name(self):
        """name(fmcomms1_source_sptr self) -> std::string"""
        return _fmcomms1_swig.fmcomms1_source_sptr_name(self)

    def symbol_name(self):
        """symbol_name(fmcomms1_source_sptr self) -> std::string"""
        return _fmcomms1_swig.fmcomms1_source_sptr_symbol_name(self)

    def input_signature(self):
        """input_signature(fmcomms1_source_sptr self) -> io_signature_sptr"""
        return _fmcomms1_swig.fmcomms1_source_sptr_input_signature(self)

    def output_signature(self):
        """output_signature(fmcomms1_source_sptr self) -> io_signature_sptr"""
        return _fmcomms1_swig.fmcomms1_source_sptr_output_signature(self)

    def unique_id(self):
        """unique_id(fmcomms1_source_sptr self) -> long"""
        return _fmcomms1_swig.fmcomms1_source_sptr_unique_id(self)

    def to_basic_block(self):
        """to_basic_block(fmcomms1_source_sptr self) -> basic_block_sptr"""
        return _fmcomms1_swig.fmcomms1_source_sptr_to_basic_block(self)

    def check_topology(self, *args, **kwargs):
        """check_topology(fmcomms1_source_sptr self, int ninputs, int noutputs) -> bool"""
        return _fmcomms1_swig.fmcomms1_source_sptr_check_topology(self, *args, **kwargs)

    def alias(self):
        """alias(fmcomms1_source_sptr self) -> std::string"""
        return _fmcomms1_swig.fmcomms1_source_sptr_alias(self)

    def set_block_alias(self, *args, **kwargs):
        """set_block_alias(fmcomms1_source_sptr self, std::string name)"""
        return _fmcomms1_swig.fmcomms1_source_sptr_set_block_alias(self, *args, **kwargs)

    def _post(self, *args, **kwargs):
        """_post(fmcomms1_source_sptr self, swig_int_ptr which_port, swig_int_ptr msg)"""
        return _fmcomms1_swig.fmcomms1_source_sptr__post(self, *args, **kwargs)

    def message_ports_in(self):
        """message_ports_in(fmcomms1_source_sptr self) -> swig_int_ptr"""
        return _fmcomms1_swig.fmcomms1_source_sptr_message_ports_in(self)

    def message_ports_out(self):
        """message_ports_out(fmcomms1_source_sptr self) -> swig_int_ptr"""
        return _fmcomms1_swig.fmcomms1_source_sptr_message_ports_out(self)

    def message_subscribers(self, *args, **kwargs):
        """message_subscribers(fmcomms1_source_sptr self, swig_int_ptr which_port) -> swig_int_ptr"""
        return _fmcomms1_swig.fmcomms1_source_sptr_message_subscribers(self, *args, **kwargs)

fmcomms1_source_sptr_swigregister = _fmcomms1_swig.fmcomms1_source_sptr_swigregister
fmcomms1_source_sptr_swigregister(fmcomms1_source_sptr)

fmcomms1_source_sptr.__repr__ = lambda self: "<gr_block %s (%d)>" % (self.name(), self.unique_id())
fmcomms1_source = fmcomms1_source.make;



