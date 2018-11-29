import sys
import argparse
import random

parser = argparse.ArgumentParser()

parser.add_argument('--trainerCount', nargs='?', default=16, type=int, help="Total trainer count for Tournament. Must be 2^n (n > 1)")
parser.add_argument('--pokemonCount', nargs='?', default=3, type=int, help="Total number of pokemons for a Trainer. Must be > 0")
args = parser.parse_args()

trainerCount = args.trainerCount
pokemonCountForTrainer = args.pokemonCount

trainerNameList = ["Ash", "Gary", "Misty", "Brook", "Jesse", "James", "Meowth", 
"Serena", "Dawn", "May", "Clemont", "Iris", "Cilan", "Bonnie", "Tracey", "Max", "ProffOak"]

firePokemons = ['Charmander', 'Charmeleon', 'Charizard', 'Vulpix', 'Ninetales', 'Growlithe', 'Arcanine', 'Ponyta', 'Rapidash', 'Magmar', 'Flareon']

waterPokemons = ['Squirtle', 'Wartortle', 'Blastoise', 'Psyduck', 'Golduck', 'Poliwag', 'Poliwhirl', 'Poliwrath', 'Tentacool', 'Tentacruel', 'Slowpoke', 
'Slowbro', 'Seel', 'Dewgong', 'Shellder', 'Cloyster', 'Krabby', 'Kingler', 'Horsea', 'Seadra', 'Goldeen', 'Seaking', 'Staryu', 'Starmie', 'Magikarp', 
'Gyarados', 'Lapras', 'Vaporeon', 'Omanyte', 'Omastar', 'Kabuto', 'Kabutops']

electricPokemons = ['Pikachu', 'Raichu', 'Magnemite', 'Magneton', 'Voltorb', 'Electrode', 'Electabuzz', 'Jolteon']

grassPokemons = ['Bulbasaur', 'Ivysaur', 'Venusaur', 'Oddish', 'Gloom', 'Vileplume', 'Paras', 'Parasect', 'Bellsprout', 'Weepinbell', 'Victreebel', 
'Exeggcute', 'Exeggutor', 'Tangela']

flyingPokemons = ['Pidgey', 'Pidgeotto', 'Pidgeot', 'Spearow', 'Fearow', 'Zubat', 'Golbat', "Farfetch'd", 'Doduo', 'Dodrio', 'Scyther', 'Aerodactyl', 
'Articuno', 'Zapdos', 'Moltres']

allPokemons = [firePokemons, waterPokemons, electricPokemons, grassPokemons, flyingPokemons]
allPokemonTypes = ['FIRE', 'WATER', 'ELECTRIC', 'GRASS', 'FLYING']

allAreas = ["Magma", "Ocean", "ElectriCity", "Forest", "Sky"]

levelRange = range(1, 5)
pokemonTypeRange = range(0, len(allPokemonTypes))

print "Trainer Count:" + str(trainerCount)
print "Pokemon Count:" + str(pokemonCountForTrainer) + '\n'

trainerDelimiter = "--"
pokemonDelimiter = "::"

for trainerID in range(trainerCount):
	print str(trainerID) + trainerDelimiter + random.choice(trainerNameList) + trainerDelimiter + random.choice(allAreas)

	for pokemonIndex in range(pokemonCountForTrainer):
		pokemonID = trainerID * pokemonCountForTrainer + pokemonIndex

		pokemonType = random.choice(pokemonTypeRange)
		pokemonName = random.choice(allPokemons[pokemonType])

		print str(pokemonID) + pokemonDelimiter + pokemonName + pokemonDelimiter + allPokemonTypes[pokemonType]

	print