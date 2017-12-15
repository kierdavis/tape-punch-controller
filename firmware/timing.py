cpu_frequency = 12e6
prescaler = 1024.0

timer_tick_frequency = cpu_frequency / prescaler
timer_tick_period = 1.0 / timer_tick_frequency

shaft_frequency = 110.0 * 5.0/6.0
shaft_period = 1.0 / shaft_frequency

reset_angle = 180.0
engage_angle = 96.0

deactivate_angle = engage_angle - 40.0
activate_angle = deactivate_angle - (4.5e-3/shaft_period)*360.0

deactivate_offset_angle = (deactivate_angle - reset_angle + 360.0) % 360.0
activate_offset_angle = (activate_angle - reset_angle + 360.0) % 360.0

deactivate_offset_time = (deactivate_offset_angle / 360.0) * shaft_period
activate_offset_time = (activate_offset_angle / 360.0) * shaft_period

deactivate_count = round(deactivate_offset_time / timer_tick_period)
activate_count = round(activate_offset_time / timer_tick_period)

print "CPU frequency = %.1f MHz" % (cpu_frequency / 1e6)
print "Timer prescaler = %d" % (prescaler)
print "Timer tick frequency = %.1f kHz" % (timer_tick_frequency / 1e3)
print "Timer tick period = %.2f us" % (timer_tick_period / 1e-6)
print "Max operational count = %d" % round(shaft_period / timer_tick_period)
print
print "Shaft rotation frequency = %.1f Hz" % (shaft_frequency)
print "Shaft rotation period = %.2f ms" % (shaft_period / 1e-3)
print
print "Solenoid activation:"
print "  Shaft angle: %.1f degrees" % (activate_angle)
print "  Offset from fb pulse: %.1f degrees / %.2f ms" % (activate_offset_angle, activate_offset_time / 1e-3)
print "  Timer count: %d" % (activate_count)
print
print "Solenoid deactivation:"
print "  Shaft angle: %.1f degrees" % (deactivate_angle)
print "  Offset from fb pulse: %.1f degrees / %.2f ms" % (deactivate_offset_angle, deactivate_offset_time / 1e-3)
print "  Timer count: %d" % (deactivate_count)
