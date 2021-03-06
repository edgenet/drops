################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################

module Drops
  module FFI
  
    # another protocol for sharing stuff
    class Drops
      class DestroyedError < RuntimeError; end
      
      # Boilerplate for self pointer, initializer, and finalizer
      class << self
        alias :__new :new
      end
      def initialize ptr
        @ptr = ptr
        @finalizer = self.class.send :create_finalizer_for, @ptr
        ObjectSpace.define_finalizer self, @finalizer
      end
      def self.create_finalizer_for ptr
        Proc.new do
          ptr_ptr = ::FFI::MemoryPointer.new :pointer
          ptr_ptr.write_pointer ptr
          Redmesh::FFI.redmesh_broker_destroy ptr_ptr
        end
      end
      
      # Constructor, creates a new drops agent
      def self.new path
        path = String(path)
        ptr = Drops::FFI.drops_new path
        
        __new ptr
      end
      
      # Destructor, ends and destroys a drops service
      def destroy
        return unless @ptr
        self_p = ::FFI::MemoryPointer.new :pointer
        self_p.write_pointer @ptr
        result = Drops::FFI.drops_destroy self_p
        
        ObjectSpace.undefine_finalizer self
        @finalizer = nil
        @ptr = nil
        result
      end
      
      # Receive next message from drops agent
      def recv
        raise DestroyedError unless @ptr
        result = Drops::FFI.drops_recv @ptr
        
        result
      end
      
      # Return handle to the drops agent, for polling
      def socket
        raise DestroyedError unless @ptr
        result = Drops::FFI.drops_socket @ptr
        
        result
      end
      
      # Self test of this class
      def self.test verbose
        verbose = !(0==verbose||!verbose) # boolean
        result = Drops::FFI.drops_test verbose
        
        result
      end
    end
    
  end
end

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
