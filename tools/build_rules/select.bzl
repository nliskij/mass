all_cpus = ['amd64', 'roborio', 'armhf']
'''All of the CPUs we are using.'''

'''A select wrapper for CPU architecture

Args:
    Values: A mapping from architecture names to other things.
        Currently recognizes amd64, roborio, and armhf.
        'else' is allowed as a default,
        'arm' is allowed instead of roborio and armhf.
Returns a select with evalueates to the correct element.
'''
def cpu_select(values):
    if 'arm' in values:
        new_values = {}
        for cpu in values:
            if cpu != 'arm':
                new_values[cpu] = values[cpu]
        new_values['armhf'] = values['arm']
        new_values['roborio'] = values['arm']
        values = new_values
    for cpu in all_cpus:
        if cpu not in values:
            if 'else' in values:
                values[cpu] = values['else']
            else:
                fail('Need to handle %s CPUs!' % cpu, 'values')
    for key in values:
        if key not in all_cpus and key != 'else':
            fail('Not sure what a %s CPU is!' % key, 'values')
    return select({
        '@//tools:cpu_k8': values['amd64'],
        '@//tools:cpu_roborio': values['roborio'],
        '@//tools:cpu_armhf': values['armhf'],
    })

'''A select wrapper for address sizes.o

Args:
    Values: A mapping from address size strings to other things.
Returns a select which evaluates to the correct element.
'''
def address_size_select(values):
    if '32' not in values:
        fail('Need to handle 32 bit addresses!', 'values')
    if '64' not in values:
        fail('Need to handle 64 bit addresses!', 'values')
    return select({
        '@//tools:cpu_k8': values['64'],
        '@//tools:cpu_roborio': values['32'],
    })

'''A select wrapper for compilers.

Args:
    Values: A mapping from compiler names (as strings) to other things.
        Currently 'gcc' and 'clang' are recognized.

Returns a select which evaluates to the correct element of values.
'''
def compiler_select(values):
    if 'gcc' not in values:
        fail('Need to handle gcc!', 'values')
    if 'clang' not in values:
        fail('Need to handle clang!', 'values')
    return select({
        '@//tools:compiler_gcc': values['gcc'],
        '@//tools:compiler_clang': values['clang'],
    })
