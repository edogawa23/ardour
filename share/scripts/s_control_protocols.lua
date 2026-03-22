ardour { ["type"] = "Snippet", name = "Control Protocol Manager" }

function factory () return function ()
	local m = ARDOUR.ControlProtocolManager:manager ()
	for p in m:control_protocol_infos ():iter () do
		print (p.name, p:active ())
		if p.name == "Generic MIDI" and not p:active () then
			m:activate (p)
		end
		if p.name == "PreSonus FaderPort" and p:active () then
			m:deactivate (p)
		end
	end
end end
