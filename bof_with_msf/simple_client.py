#!/usr/bin/python

import socket
import struct
import sys

if len(sys.argv) != 2:
    print "Usage: " + sys.argv[0] + " [port]"
    sys.exit(1)

DEST_IP = '127.0.0.1'
DEST_PORT = int(sys.argv[1])
#MESSAGE = "Hello\n"
MESSAGE = 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAnAASAAoAATAApAAUAAqAAVAArAAWAAsAAXAAtAAYAAuAAZAAvAAwAAxAAyAAzA%%A%sA%BA%$A%nA%CA%-A%(A%DA%;A%)A%EA%aA%0A%FA%bA%1A%GA%cA%2A%HA%dA%3A%IA%eA%4A%JA%fA%5A%KA%gA%6A%LA%hA%7A%MA%iA%8A%NA%jA%9A%OA%kA%PA%lA%QA%mA%RA%nA%SA%oA%TA%pA%UA%qA%VA%rA%WA%sA%XA%tA%YA%uA%ZA%vA%wA%xA%yA%zAs%AssAsBAs$AsnAsCAs-As(AsDAs;As)AsEAsaAs0AsFAsbAs1AsGAscAs2AsHAsdAs3AsIAseAs4AsJAsfAs5AsKAsgAs6AsLAshAs7AsMAsiAs8AsNAsjAs9AsOAskAsPAslAsQAsmAsRAsnAsSAsoAsTAspAsUAsqAsVAsrAsWAssAsXAstAsYAsuAsZAsvAswAsxAsyAszAB%ABsABBAB$ABnABCAB-AB(ABDAB;AB)ABEABaAB0ABFABbAB1ABGABcAB2ABHABdAB3ABIABeAB4ABJABfAB5ABKABgAB6ABLABhAB7ABMABiAB8ABNABjAB9ABOABkABPABlABQABmABRABnABSABoABTABpABUABqABVABrABWABsABXABtABYABuABZABvABwABxAByABzA$%A$sA$BA$$A$nA$CA$-A$(A$DA$;A$)A$EA$aA$0A$FA$bA$1A$GA$cA$2A$HA$dA$3A$IA$eA$4A$JA$fA$5A$KA$gA$6A$LA$hA$7A$MA$iA$8A$NA$jA$9A$OA$kA$PA$lA$QA$mA$RA$nA$SA$oA$TA$pA$UA$qA$VA$rA$WA$sA$XA$tA$YA$uA$ZA$vA$wA$xA$yA$zAn%AnsAnBAn$AnnAnCAn-An(AnDAn;An)AnEAnaAn0AnFAnbAn1AnGAncAn2AnHAndAn3AnIAneAn4AnJAnfAn5AnKAngAn6AnLAnhAn7AnMAniAn8AnNAnjAn9AnOAnkAnPAnlAnQAnmAnRAnnAnSAnoAnTAnpAnUAn'

def convert(message):
    raw = ''
    raw += struct.pack("<I", len(message))
    raw += message
    return raw

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((DEST_IP, DEST_PORT))
s.send(convert(MESSAGE))

data = s.recv(1024)
s.close()

print "Received data: ", data
