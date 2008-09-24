-- statusd_jicknan.lua - Used by Jick Nan <jick.nan@gmail.com>
--
-- Public domain
--
-- %cpufreq - get the current CPU frequency in MHz, according to
-- /sys/devices/system/cpu/cpuX/cpufreq/scaling_cur_freq.
--
-- network monitor, according to /proc/net/dev
-- 
-- The "cpu" option to the statusd settings for cpufreq modifies which
-- cpu we look at.

local defaults= {
	update_interval = 2 * 1000, -- ms
	cpu = 0,
	interface = "eth0",
}

local positions = {}
local last = {}

local settings = table.join(statusd.get_config("jicknan"), defaults)

function get_cpufreq ()
        local f = io.open('/sys/devices/system/cpu/cpu' .. settings.cpu ..
		'/cpufreq/scaling_cur_freq')
	local cpufreq = f:read('*a') / 1000
	f:close()
        
        return tostring(cpufreq)
end

--
-- tokenize the string
--
local function tokenize (str)
	local ret = {}
	local i = 0
	local k = nil

	for k in string.gfind(str, '(%w+)') do
		ret[i] = k
		i = i + 1
	end

	return ret
end

--
-- sanity check for network device
--
local function sanity_check ()
	local f = io.open('/proc/net/dev', 'r')

	if not f then
		return false
	end

	local s = f:read('*line')
	s = f:read('*line') -- the second line

	local t = tokenize(s)
	local n = table.getn(t)
	local i = 0

	for i = 0,n do
		if t[i] == "bytes" then
			positions[0] = i
			break
		end
	end

	i = positions[0] + 1

	for i = i,n do
		if t[i] == "bytes" then
			positions[1] = i
			break
		end
	end

	if not positions[0] or not positions[1] then
		return false
	end

	s = f:read('*a')
	if not string.find(s, settings.interface) then
		return false	-- the interface does not exist
	end

	return true
end

--
-- parse the network infomation
--
local function parse_network_info()
	local s
	local lin, lout

	for s in io.lines('/proc/net/dev') do
		local f = string.find(s, settings.interface)
		if f then
			local t = tokenize(s)
			return t[positions[0]], t[positions[1]]
		end
	end

	return nil, nil
end

function update_jicknan()
	-- cpufreq
	local cpufreq = get_cpufreq()
	statusd.inform("jicknan_cpufreq", cpufreq)

	-- network infomation
	local s
	local lin, lout

	local function fmt(num)
		return(string.format("%.1fK", num))
	end

	lin, lout = parse_network_info()
	last[0], lin = lin, lin - last[0]
	last[1], lout = lout, lout - last[1]

	local kbsin = lin / settings.update_interval
	local kbsout = lout / settings.update_interval

	statusd.inform("jicknan_netin", fmt(kbsin))
	statusd.inform("jicknan_netout", fmt(kbsout))

	-- timer
	jicknan_timer:set(settings.update_interval, update_jicknan)
end

function init_jicknan()

	-- network monitor
	if sanity_check() then
		last[0], last[1] = parse_network_info()
		update_jicknan()
	end

end

jicknan_timer = statusd.create_timer()
init_jicknan()
